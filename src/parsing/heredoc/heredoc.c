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

int    heredoce(char *limiter,t_var *data)
{
    char *line;
    int fds[2]; // array of two elements 

    if(pipe(fds) == -1)
        return(2);
    while (1)
    {
        line = readline("> ");
        //printf("%s\n", line);
        if(!line || ft_strcmp(line, limiter) == 0) // if null(read line detect the end of file ) or limiter
            break;
        write(fds[1], line, ft_strlen(line));
        write(fds[1], "\n", 1);
        free(line);
    }
    //free(line);
    // close(fds[1]); // close the write end
    data->in_file = fds[0];
    return(0); // return the read end
}
