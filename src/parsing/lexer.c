/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:51:05 by nahilal           #+#    #+#             */
/*   Updated: 2025/04/29 18:54:15 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parsing *handle_quote_space(t_lexer_data *data, t_parsing *head, t_env *envs)
{
    char *tmp;
    
    tmp = NULL;
    if(data->str[data->i] == 0)
        return(head);
    if(data->str[data->i + 1] == ' ')
    {
        head = ft_save(tmp, head, WHITE_SPACE, 1, data->state, envs);
        data->i++;
    }
    return(head);
}

t_parsing *process_quote_content(t_lexer_data *data, t_parsing *head, t_env *envs)
{
    char *tmp;
    int j;
    enum e_type c;
    
    j = 0;
    tmp = g_collector(data->len + 1, envs);
    while(data->str[data->i] && data->str[data->i] != data->quote_type)
    {
        tmp[j++] = data->str[data->i++];
        c = check_token(data->str, data->i);
        if(c == data->quote_type)
        {
            if(c == 34)
                data->state = INDQUOTE;
            else
                data->state = INQUOTE;
            tmp[j] = '\0';
            head = ft_save(tmp, head, -1, 0, data->state, envs);
            data->state = GENERAL;
            head = ft_save(data->str, head, c, c, data->state, envs);
            break;
        }
    }
    return(handle_quote_space(data, head, envs));
}

t_parsing *handle_word_space(t_lexer_data *data, t_parsing *head, t_env *envs)
{
    char *tmp;
    
    tmp = NULL;
    if(data->str[data->i] == 0)
        return(head);
    if(data->str[data->i + 1] == ' ')
    {
        head = ft_save(tmp, head, WHITE_SPACE, 1, data->state, envs);
        data->i++;
    }
    return(head);
}

t_parsing *handle_quote_token(t_lexer_data *data, t_parsing *head, t_env *envs)
{
    head = ft_save(data->str, head, data->quote_type, data->str[data->i], data->state, envs);
    data->i++;
    if(data->str[data->i] == data->quote_type)
    {
        head = ft_save(data->str, head, data->quote_type, data->str[data->i], data->state, envs);
        data->i++;
        data->i--;
        return(head);
    }
    return(process_quote_content(data, head, envs));
}

t_parsing *handle_word_token(t_lexer_data *data, t_parsing *head, t_env *envs)
{
    char *tmp;
    int j;
    enum e_type c;
    int t;
    
    t = -1;
    tmp = g_collector(data->len + 1, envs);
    j = 0;
    c = -1;
    while(c == -1 && data->str[data->i])
    {
        tmp[j++] = data->str[data->i++];
        c = check_token(data->str, data->i);
        if(c != -1 || data->str[data->i] == 0)
        {
            tmp[j] = '\0';
            head = ft_save(tmp, head, t, 0, data->state, envs);
            if(c != -1)
                data->i--;
            break;
        }
    }
    return(handle_word_space(data, head, envs));
}

t_parsing *handle_double_redirect(t_lexer_data *data, t_parsing *head, t_env *envs)
{
    char *tmp;
    int t;
    enum e_type c;
    
    c = data->redirect_type;
    t = c;
    if(c == DREDIR_OUT)
        c = '>';
    else
        c = '<';
    tmp = g_collector(3, envs);
    tmp[0] = c;
    tmp[1] = c;
    tmp[2] = 0;
    head = ft_save(tmp, head, t, 0, data->state, envs);
    data->i += 2;
    data->i--;
    return(head);
}

t_parsing *handle_env_token(t_lexer_data *data, t_parsing *head, t_env *envs)
{
    char *tmp;
    int j;
    enum e_type c;
    
    tmp = g_collector(data->len + 1, envs);
    j = 0;
    while(data->str[data->i])
    {
        c = check_token(data->str, data->i);
        if(c == WHITE_SPACE || c == PIPE_LINE || c == DQUOTE || c == QUOTE || 
           c == REDIR_OUT || c == REDIR_IN || c == HERE_DOC || c == DREDIR_OUT)
            break;
        tmp[j] = data->str[data->i];
        data->i++;
        j++;
    }
    tmp[j] = 0;
    data->state = ENV_STRING;
    head = ft_save(tmp, head, WORD, 0, data->state, envs);
    data->i--;
    return(head);
}

t_parsing *handle_spaces(t_lexer_data *data, t_parsing *head, t_env *envs)
{
    char *tmp;
    
    tmp = NULL;
    if(data->str[data->i] == ' ')
        head = ft_save(tmp, head, WHITE_SPACE, 1, data->state, envs);
    while(data->str[data->i] == ' ')
        data->i++;
    data->state = GENERAL;
    return(head);
}

t_parsing *process_token(t_lexer_data *data, t_parsing *head, t_env *envs)
{
    enum e_type c;
    
    c = check_token(data->str, data->i);
    if(c == ENV)
        return(handle_env_token(data, head, envs));
    else if(c == DREDIR_OUT || c == HERE_DOC)
    {
        data->redirect_type = c;
        return(handle_double_redirect(data, head, envs));
    }
    else if(c == -1)
        return(handle_word_token(data, head, envs));
    else if(c == 34 || c == 39)
    {
        data->quote_type = c;
        return(handle_quote_token(data, head, envs));
    }
    else
        return(ft_save(data->str, head, c, data->str[data->i], data->state, envs));
}

t_parsing *lexer(char *str, t_env *envs)
{
    t_parsing *head;
    t_lexer_data data;
    
    head = NULL;
    data.str = str;
    data.i = 0;
    data.len = ft_strlen(str);
    data.state = GENERAL;
    
    while(data.str[data.i])
    {
        head = handle_spaces(&data, head, envs);
        head = process_token(&data, head, envs);
        if(data.str[data.i] == 0)
            break;
        data.i++;
    }
    return(head);
}