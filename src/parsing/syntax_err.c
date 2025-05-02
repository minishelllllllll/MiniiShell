/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:42:31 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/02 17:51:15 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parsing *check_quote(t_parsing *curr)
{
    char c;

    if(curr->type == '\"' || curr->type == '\'')
    {
        c = curr->type;
        curr = curr->next;
        if(!curr)
            return(error_print("syntax error \"unclosed quotes\"\n"),NULL);
        while(curr->type != c)
        {
            if(!curr)
                return(error_print("syntax error \"unclosed quotes\"\n"),NULL);
            curr = curr->next;     
        }
    }
    return(check_redirection(curr));
}

t_parsing *check_pipe(t_parsing *curr, int len)
{
    if(curr->type == '|' && len == 0)
        return(error_print("syntax error near unexpected token '|'\n"),NULL);
    else if(curr->type == '|')
    {
        curr = curr->next;
        len++;
        if(!curr )
            return(error_print("syntax error near unexpected token '|'\n"),NULL);    
        if(curr->type == '|')
            return(error_print("syntax error near unexpected token '||'\n"),NULL);
        while (curr)
        {
            if(curr->type != ' ')
                break;
            curr = curr->next;
        }
    }
    return(check_quote(curr));
}

int syntax_err(t_parsing *head)
{
    t_parsing *curr;
    int len;
    
    len = 0;
    curr = skip_space(head);
    while (curr)
    {
        curr = check_pipe(curr,len);
        if(!curr)
            return(0);
        len++;
        curr = curr->next;
    }
    return(1);
}