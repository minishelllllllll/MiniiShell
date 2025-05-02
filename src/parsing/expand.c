/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:31:13 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/02 19:01:48 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parsing *expand(t_parsing *head)
{
    char *str;
    int i;
    int j;

    if(!head)
        return(NULL);
    if(head->state == 2)
    {
        str = head->content;
        i = 0;
        while(str[i] == ' ')
            i++;
        j = i;
        while(str[i])
        {
            if(str[j] == '$')
            {
                i++;
                printf("nahilal\n");
                // printf("%s\n",str + i);
                return(NULL);
            }
            i++;
        }
        return(printf("%s\n",head->content),NULL);    
    }
    if(head->state == 1)
        return(printf("%s\n",head->content),NULL);    
    return(head);
}