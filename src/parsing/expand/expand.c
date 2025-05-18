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

char *ft_charjoin(char *str,char c)
{
    int len;
    int i;
    char *s;

    if(!str)
        return(NULL);
    i = 0;
    len = ft_strlen(str);
    s = malloc(len + 2);
    while(str[i])
    {
        s[i] = str[i];
        i++;
    }
    s[i++] = c;
    s[i]= 0;
    return(s);
}
char *check_env_general(char *str,t_env *envp)
{
    int i;
    t_env *tmp;
    char *s;

    i = 0;
    tmp = envp;
    s = malloc(2);
    s[0] = 0;
    while(str[i] && str[i] == ' ')
        i++;
    while(str[i])
    {
        if(str[i] == '$')
        {
            i++;
            while(tmp)
            {
                if(ft_strncmp(tmp->key,str + i,ft_strlen(tmp->key)) == 0)
                {
                    i+= ft_strlen(tmp->key);
                    if(ft_isalnum(str[i]) == 1)
                    {
                        i++;
                        while(str[i] && str[i] != ' ')
                        {
                            if(str[i] == ' ')
                                break;
                            i++;
                        }
                        while(str[i] && str[i] == ' ')
                            i++;
                        break;
                    }
                    s = ft_strjoin(s,tmp->value);
                    break;
                }
                tmp = tmp->next;
            }
            if(!tmp)
            {
                while(str[i])
                {
                    if(str[i] == ' ' || ft_isalnum(str[i]) == 0)
                        break;
                    i++;
                }
                while(str[i]&& str[i] == ' ')
                    i++;
            }
            continue;
        }
        s = ft_charjoin(s,str[i]);
        i++;
    }
    return(s);
}


t_parsing *expand(t_parsing *head,t_env *envp,t_var *data)
{
    if(!head)
        return(NULL);
    // if(head->type != PIPE_LINE)
    //     return(ft_send(t_var *data))

    if(head->type == DREDIR_IN || head->type == REDIR_IN) 
    {
        if(ft_redirect_in(head) == 2)
            return(NULL);
        head = head->next;
        return(head);
    } 
    if(head->state == 3)
    {
        head->content = check_env_general(head->content,envp);
        printf("%s\n",head->content);
        if(!head->content)
            return(NULL);
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
