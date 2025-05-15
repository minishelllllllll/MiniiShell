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

t_parsing *expand(t_parsing *head,t_env *envp,t_var *data)
{
    if(!head)
        return(NULL);
    // if(head->type != PIPE_LINE)
    //     return(ft_send(t_var *data))


    if(head->type == DREDIR_OUT || head->type == REDIR_IN) 
    {
        if(ft_here_doc(head) == 2)
            return(NULL);
        head = head->next;
        return(head);
    } 
    if(head->state == 0 && head->type != DQUOTE && head->type != QUOTE)
    {
        data->s[data->l] = ft_strdup(head->content);
        printf("%s\n",data->s[data->l]);
        data->l++;
        return(head);
    }
    if(head->state == 2)
    {
        if(ft_double(head->content,envp,data) == 2)
            return(NULL);
        data->s[data->l] = ft_strdup(data->s1);
        printf("%s\n",data->s[data->l]);
        data->l++;
        return(head);
    }
    if(head->state == 1)
    {
        data->s[data->l] = ft_strdup(head->content);
        printf("%s\n",data->s[data->l]);
        data->l++;
        return(head);
    }
    return(head);
}
