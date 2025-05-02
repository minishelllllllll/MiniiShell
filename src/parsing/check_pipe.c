/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:42:31 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/02 14:42:49 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_pipee(t_parsing *head)
{
    t_parsing *curr;
    int len;
    
    curr = head;
    len = 0;
    while(curr->type == ' ' && curr)
        curr = curr->next;
    while (curr)
    {
        if(curr->type == '|' && len == 0)
            return(error_print("syntax error near unexpected token '|'\n"),1);
        else if(curr->type == '|')
        {
            curr = curr->next;
            len++;
            if(!curr || curr->type == '|')
                return(error_print("syntax error near unexpected token '|'\n"),1);    
            while (curr)
            {
                if(curr->type != ' ')
                    break;
                curr = curr->next;
            }
        }
        len++;
        curr = curr->next;
    }
    return(0);
}