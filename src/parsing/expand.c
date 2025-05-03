/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:31:13 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/03 16:18:36 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parsing *expand(t_parsing *head,char **envp)
{
    char *str;
    int i;
    int j;
    t_env *res;
    
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
                j++;
                if(str[j] < 'A' ||str[j] > 'Z')
                    break;
                res = list_envs(envp);
                while(res)
                {
                    if(strcmp(res->key,str + j) == 0)
                        return(printf("%s\n",res->value),NULL);
                    res = res->next;
                }
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