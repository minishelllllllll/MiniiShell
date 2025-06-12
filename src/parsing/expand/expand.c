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
int check_odd(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] != '$')
            break;
        i++;
    }
    return(i);
}
char *check_env_general(char *str, t_env *envp, t_var *data)
{
    int i;
    int len;
    t_env *tmp;
    (void)data;
    char *s;

    i = 0;
    len = 0;
    tmp = envp;
    s = malloc(2);
    s[0] = 0;
    len = check_odd(str);
    if(len % 2 == 1)
        len--;
    while(str[i] && str[i] == ' ')
        i++;
    i += len;
    while(str[i])
    {
        if(str[i] == '$')
        {
            i++;
            tmp = envp;
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

int ft_split_expand(char **s1, t_var *data)
{
    int i;
    i = 0;

    if(!s1)
        return(0);
    while(s1[i])
    {
        data->s[data->l] = ft_strdup(s1[i]);
        if(!data->s[data->l])
            return(0);
        data->l++;
        i++;
    }
    return(1);
}

t_parsing *expand(t_parsing *head, t_env *envp, t_var *data, t_cmd **cmd)
{
    char quote_type;
    char *combined;
    char *quoted_content;
    t_parsing *content_token;
    t_parsing *quote_start;
    char **split_expand;
    int flag;

    if(!head)
        return(NULL);
    
    if(head->type == PIPE_LINE)
    {
        *cmd = ft_send(data, *cmd);
        data->l = 0;
        data->in_file = -1;
        data->out_file = -1;
        return(head);
    }
    
    if(head->type == REDIR_IN)
    {
        if(ft_redirect_in(head, data) == 2)
            return(NULL);
        head = head->next;
        return(head);
    }
    
    if(head->type == HERE_DOC)
    {
        flag = 0;
        head = head->next;
        if(!head)
            return(NULL);
        if(head->type == WHITE_SPACE)
            head = head->next;
        if(head->type == DQUOTE)
            flag = 2;
        else if(head->type == QUOTE)
            flag = 1;
        else
            flag = 0;
        if(heredoce(head->content, data ,flag) == 2)
            return(NULL);
        return(head);
    }
    
    if(head->type == DREDIR_OUT || head->type == REDIR_OUT) 
    {
        if(ft_redirect_out(head, data) == 2)
            return(NULL);
        head = head->next;
        return(head);
    }
    
    if(head->state == 3)
    {
        // data->s[data->l] = check_env_general(head->content, envp, data);
        split_expand = ft_split(check_env_general(head->content, envp, data),' ');
        if(ft_split_expand(split_expand,data) == 0)
            return(NULL);
        if(!head->content)
            return(NULL);
        return(head);
    }
    if(head->state == 0 && head->type != DQUOTE && head->type != QUOTE)
    {
        if(head->next && (head->next->type == DQUOTE || head->next->type == QUOTE))
        {
            quote_type = head->next->type;
            content_token = head->next->next;
            if(content_token && content_token->next && content_token->next->type == quote_type)
            {
                if(quote_type == DQUOTE)
                    quoted_content = check_env_general(content_token->content, envp, data);
                else
                    quoted_content = ft_strdup(content_token->content);
                combined = ft_strjoin(head->content, quoted_content);
                free(quoted_content);
                data->s[data->l] = combined;
                data->l++;
                return(content_token->next);
            }
        }
        if(ft_strchr(head->content, '=') != NULL && head->next)
        {
            quote_start = head->next;
            if(quote_start && (quote_start->type == DQUOTE || quote_start->type == QUOTE))
            {
                quote_type = quote_start->type;
                content_token = quote_start->next;
                
                if(content_token && content_token->next && content_token->next->type == quote_type)
                {
                    if(quote_type == DQUOTE)
                        combined = ft_strjoin(head->content, check_env_general(content_token->content, envp, data));
                    else
                        combined = ft_strjoin(head->content, content_token->content);
                    data->s[data->l] = combined;
                    data->l++;
                    return(content_token->next);
                }
            }
        }
        
        if(head->type != WHITE_SPACE)
        {
            data->s[data->l] = ft_strdup(head->content);
            data->l++;
        }
        return(head);
    }
    
    if(head->state == 2)
    {
        if(ft_double(head->content, envp, data) == 2)
            return(NULL);
        data->s[data->l] = ft_strdup(data->s1);
        data->l++;
        return(head);
    }
    
    if(head->state == 1)
    {
        data->s[data->l] = ft_strdup(head->content);
        data->l++;
        return(head);
    }
    
    return(head);
}


// t_parsing *expand(t_parsing *head, t_env *envp, t_var *data, t_cmd **cmd)
// {
//     char *result;
//     char *combined;
//     char *quoted_content;

//     if(!head)
//         return(NULL);
    
//     if(head->type == PIPE_LINE)
//     {
//         *cmd = ft_send(data, *cmd);
//         data->l = 0;
//         data->in_file = -1;
//         data->out_file = -1;
//         return(head);
//     }
    
//     if(head->type == REDIR_IN)
//     {
//         if(ft_redirect_in(head, data) == 2)
//             return(NULL);
//         head = head->next;
//         return(head);
//     }
    
//     if(head->type == HERE_DOC)
//     {
//         head = head->next;
//         if(!head)
//             return(NULL);
//         if(heredoce(head->content, data) == 2)
//             return(NULL);
//         head = head->next;
//         return(head);
//     }
    
//     if(head->type == DREDIR_OUT || head->type == REDIR_OUT) 
//     {
//         if(ft_redirect_out(head, data) == 2)
//             return(NULL);
//         head = head->next;
//         return(head);
//     }
    
//     if(head->state == 3)
//     {
//         data->s[data->l] = check_env_general(head->content, envp, data);
//         printf("str 1 => %s\n",data->s[data->l]);
//         data->l++;
//         if(!head->content)
//             return(NULL);
//         return(head);
//     }
//     if(head->state == 0 && head->type != DQUOTE && head->type != QUOTE)
//     {
//         if(head->next && (head->next->type == DQUOTE || head->next->type == QUOTE))
//         {
//             head = head->next;
//             if(head && head->next && head->next->type == head->type)
//             {
//                 if(head->type == DQUOTE)
//                     quoted_content = check_env_general(head->content, envp, data);
//                 else
//                     quoted_content = ft_strdup(head->content);
//                 combined = ft_strjoin(head->content, quoted_content);
//                 free(quoted_content);
//                 data->s[data->l] = combined;
//         printf("str 2 => %s\n",data->s[data->l]);
//                 data->l++;
//                 return(head);
//             }
//         }
//         if(strchr(head->content, '=') != NULL && head->next)
//         {
//             if(head->next && (head->next->type == DQUOTE || head->next->type == QUOTE))
//             {
//                 head = head->next;
//                 if(head && head->next && head->next->type == head->type)
//                 {
//                     if(head->type == DQUOTE)
//                         combined = ft_strjoin(head->content, check_env_general(head->content, envp, data));
//                     else
//                         combined = ft_strjoin(head->content, head->content);
//                     data->s[data->l] = combined;
//         printf("str 3 => %s\n",data->s[data->l]);
//                     data->l++;
//                     return(head);
//                 }
//             }
//         }
        
//         if(head->type != WHITE_SPACE && head->type != DQUOTE && head->type != QUOTE)
//         {
//             data->s[data->l] = ft_strdup(head->content);
//             printf("str 4 => %s\n",data->s[data->l]);
//             data->l++;
//         }
//         return(head);
//     }
//     if(head->type == DQUOTE || head->type == QUOTE)
//     {
//         if(head->next && head->next->next && head->next->next->type == head->type)
//         {
//             if(head->type == DQUOTE)
//                 result = check_env_general(head->next->content, envp, data);
//             else
//                 result = ft_strdup(head->next->content);
//             data->s[data->l] = result;
//         printf("str 5 => %s\n",data->s[data->l]);

//             data->l++;
//             return(head->next->next);
//         }
//         if(head->next && head->next->type == head->type)
//         {
//             data->s[data->l] = ft_strdup("");
//         printf("str 6 => %s\n",data->s[data->l]);

//             data->l++;
//             return(head->next);
//         }
//     }
    
//     if(head->state == 2)
//     {
//         if(ft_double(head->content, envp, data) == 2)
//             return(NULL);
//         data->s[data->l] = ft_strdup(data->s1);
//         printf("str 7 => %s\n",data->s[data->l]);

//         data->l++;
//         return(head);
//     }
    
//     if(head->state == 1)
//     {
//         data->s[data->l] = ft_strdup(head->content);
//         printf("str 8 => %s\n",data->s[data->l]);

//         data->l++;
//         return(head);
//     }
    
//     return(head);
// }