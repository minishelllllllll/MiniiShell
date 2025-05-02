/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:53:24 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/02 14:20:41 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_quote(t_parsing *head)
{
    t_parsing *curr;
    char c;
    
    curr = head;
    while(curr)
    {
        if(curr->type == '\"' || curr->type == '\'')
        {
            c = curr->type;
            curr = curr->next;
            if(!curr)
                return(error_print("syntax error \"unclosed quotes\"\n"),1);
            while(curr->type != c)
            {
                if(!curr)
                    return(error_print("syntax error \"unclosed quotes\"\n"),1);
                curr = curr->next; 
            }
        }
        curr = curr->next;
    }
    return(0);
}