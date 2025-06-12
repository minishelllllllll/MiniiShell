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

int    heredoce(char *limiter,t_var *data, int flag)
{
    char *line;
    int fds[2];
    // t_parsing   *heredoce_lexer;

    if(pipe(fds) == -1)
        return(2);
    while (1)
    {
        line = readline("> ");
        // heredoce_lexer = lexer(line);

        if(!line || ft_strcmp(line, limiter) == 0)
            break;
        write(fds[1], line, ft_strlen(line));
        write(fds[1], "\n", 1);
        free(line);
    }
    close(fds[1]);
    data->in_file = fds[0];
    return(0);
}
