/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:02:05 by marvin            #+#    #+#             */
/*   Updated: 2025/05/23 17:02:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void sig_ignore()
{
    signal(SIGINT, SIG_IGN); // ignore sigint while parent wait child to dont affect parent 
    signal(SIGQUIT, SIG_IGN);
}

void read_heredoc(int **fds, char *delimiter)
{
    char *line;

    while (1)
    {
        line = readline("> ");
        if(!line)
        {
            ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
            ft_putstr_fd(delimiter, 2);
            ft_putstr_fd("')\n", 2);
            return;
        }
        if(ft_strcmp(line, delimiter) == 0)
            return;
        write((*fds)[1], line, ft_strlen(line));
        write((*fds)[1], "\n", 1);
        free(line);
    }
    return;
}


int    heredoce(char *delimiter,t_var *data, int flag)
{
    // char *line;
    int *fds;
    int (state), (pid);

    (void)flag;
    fds = malloc(2 * sizeof(int));
    if(pipe(fds) == -1)
        return(2);
    pid = fork();
    if(pid == -1)
    {
        close(fds[0]);  // Clean up file descriptors
        close(fds[1]);
        return(2);
    }
    if (pid == 0)
    {
        signal(SIGINT, sig_heredoc);
        close(fds[0]);
        read_heredoc(&fds, delimiter);
    }
    else
    {
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
    }
    return(0);
}
