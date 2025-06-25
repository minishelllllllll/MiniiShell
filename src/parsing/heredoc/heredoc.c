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

void    signalhandler(int sig)
{
    (void) sig;
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
    if (pid == 0)
    {
        signal(SIGINT, signalhandler);
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
        data->in_file = fds[0];
        exit(0);
    }
    else
    {
        signal(SIGINT, SIG_IGN);        
        waitpid(pid, &state, 0);
        signal(SIGINT, my_handller);        

        if (WIFSIGNALED(state))
		{
            G_EXIT_STATUS = state + 128;
			if (G_EXIT_STATUS == 131)
               printf("Quit: 3\n");
        }
    }
    return(0);
}
