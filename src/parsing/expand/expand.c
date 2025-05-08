/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:31:13 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/06 18:51:16 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void ft_general(char *str)
{
    printf("%s",str);
}
t_parsing *expand(t_parsing *head,t_env *envp)
{
    if(!head)
        return(NULL);
    if(head->state == 0 && head->type != DQUOTE && head->type != QUOTE)
        return(ft_general(head->content),head);
    if(head->state == 2)
    {
        if(ft_double(head->content,envp,0,0) == 2)
            return(NULL);
        return(head);
    }
    if(head->state == 1)
        return(printf("%s\n",head->content),NULL); 
      
    return(head);
}
