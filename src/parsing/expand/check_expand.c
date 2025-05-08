/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:30:22 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/08 18:30:22 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int check_expand(t_parsing *head,t_env *envp)
{
    while(head)
    {
        while(head && head->type != PIPE_LINE)
        {
            head = expand(head,envp);
            head = head->next;
        }
        if(!head)
        {
            printf("\n");
            return(2);
        }  
        printf("|");
        head = head->next;
    }
    return(0);
}