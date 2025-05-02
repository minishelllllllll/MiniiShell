/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:41:28 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/02 14:43:08 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_token(char *str, int i)
{
    if(str[i] == '\'')
        return(QUOTE);
    else if(str[i] == '\"')
        return(DQUOTE);
    else if(str[i] == ' ')
        return(WHITE_SPACE);
    else if(str[i] == '\n')
        return(NEW_LINE);
    else if(str[i] == '\\')
        return(ESCAPE);
    else if(str[i] == '$')
        return(ENV);
    else if(str[i] == '|')
        return(PIPE_LINE);                    
    else if(str[i] == '<')
        return(REDIR_OUT);
    else if(str[i] == '>')
            return(REDIR_IN);
    else
        return(WORD);
}