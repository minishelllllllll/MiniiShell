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

void    sig_heredoc(int sig)
{
    (void) sig;
    ft_putchar_fd('\n', 1);
    exit(130);
}

int    heredoce(char *limiter,t_var *data, int flag)
{
    char *line;
    int fds[2];
    int state;
    (void)flag;

    if(pipe(fds) == -1)
        return(2);
    
    int pid = fork();
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
        while (1)
        {
            line = readline("> ");
            if(!line)
            {
                ft_putstr_fd("minishell: warning: here-document at line delimited by end-of-file (wanted `", 2);
                ft_putstr_fd(limiter, 2);
                ft_putstr_fd("')\n", 2);
                break;
            }
            if(ft_strcmp(line, limiter) == 0)
                break;
            write(fds[1], line, ft_strlen(line));
            write(fds[1], "\n", 1);
            free(line);
        }
        close(fds[1]);
        exit(0);
    }
    else
    {
        signal(SIGINT, SIG_IGN); // ignore sigint while parent wait child to dont affect parent 
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
