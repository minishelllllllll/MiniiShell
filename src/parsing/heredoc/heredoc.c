/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:02:05 by marvin            #+#    #+#             */
/*   Updated: 2025/06/29 19:20:19 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


char *expand_var(char *line, t_env *envp, int i)
{
    char *result;
    int start;
    int len;
    t_env *tmp;
    
    if (!line)
        return (NULL);
    result = ft_strdup("", envp);
    if (!result)
        return (NULL);
    while (line[i])
    {
        if (line[i] == '$')
        {
            i++;
            start = i;
            while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
                i++;
            len = i - start;   
            if (len > 0)
            {
                tmp = envp;
                while (tmp)
                {
                    if (ft_strcmp(tmp->key, ft_substr(line, start, len)) == 0)
                    {
                        result = ft_strjoin(result, tmp->value, envp);
                        if(!result)
                            return(NULL);
                        break;
                    }
                    tmp = tmp->next;
                }
            }
        }
        else
        {
            result = join_char(result, line[i]);
            if (!result)
                return (NULL);
            i++;
        }
    }
    return (result);
}
void closing(int *fds)
{
    close(fds[0]);  // Clean up file descriptors
    close(fds[1]);
}

void error_msg_heredoc(char *delimiter)
{
    ft_putstr_fd("minishell: warning: here-document at line delimited by end-of-file (wanted `", 2);
    ft_putstr_fd(delimiter, 2);
    ft_putstr_fd("`)\n", 2);
}

void run_heredoc(int *fds, char *delimiter)
{
    char *line;

    signal(SIGINT, sig_heredoc);
    close(fds[0]);
    while (1)
    {
        line = readline("> ");
        if(!line)
        {
            error_msg_heredoc(delimiter);
            break;
        }
        if(ft_strcmp(line, delimiter) == 0)
            break;
        write(fds[1], line, ft_strlen(line));
        write(fds[1], "\n", 1);
        free(line);
    }
    close(fds[1]);
    exit(0);
}

int wait_heredoc(t_var *data, int pid, int *fds)
{
    int state;

    sig_ignore();
    waitpid(pid, &state, 0);
    close(fds[1]);
    if (WIFEXITED(state))
    {
        G_EXIT_STATUS = WEXITSTATUS(state);
        if(G_EXIT_STATUS == 130)
        {
            close(fds[0]);  // Clean up file descriptors
            return(2);
        }
    }
    data->in_file = fds[0];
    return(0);
}

int    heredoce(char *delimiter,t_var *data, int flag, t_env *envp)
{
    int *fds;
    int pid;

    (void)flag;
    (void)envp;
    fds = malloc(2 * sizeof(int));
    if(pipe(fds) == -1)
        return(2);
    pid = fork();
    if(pid == -1)
        return(closing(fds), 2);
    if (pid == 0)
        run_heredoc(fds, delimiter);
    else
    {
        if(wait_heredoc(data, pid, fds) == 2)
            return(2);
    }
    return(0);
}

