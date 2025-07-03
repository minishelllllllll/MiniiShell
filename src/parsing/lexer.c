/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:51:05 by nahilal           #+#    #+#             */
/*   Updated: 2025/04/29 18:54:15 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_if_env(t_env *envs, t_help *data,char *str,t_parsing *head)
{
	if (data->c == ENV)
	{
		data->tmp = g_collector(data->len + 1, envs);
		data->j = 0;
		while (str[data->i])
		{
			data->c = check_token(str,data->i);
			if(data->c == WHITE_SPACE || data->c == PIPE_LINE ||data->c == DQUOTE || data->c == QUOTE || data->c == REDIR_OUT
				|| data->c == REDIR_IN || data->c == HERE_DOC || data->c == DREDIR_OUT)
				return (2);
			data->tmp[data->j] = str[data->i];
			data->i++;
			data->j++;
		}
		data->tmp[data->j] = 0;
		data->state = ENV_STRING;
		head = ft_save(data->tmp,head,WORD,0,data->state, envs);
		if(str[data->i] == 0)
			return (2);
		return (1);
	}
	return (0);
}
t_parsing *lexer(char *str, t_env *envs)
{
	t_parsing *head;
	t_help data;
	int res;

	head = NULL;
	data.state = GENERAL;
	data.i = 0;
	data.j = 0;
	data.c = 0;
	data.len = ft_strlen(str);
	while(str[data.i])
	{
		if(str[data.i] == ' ')
			head = ft_save(data.tmp,head,WHITE_SPACE,1,data.state, envs);
		while(str[data.i] == ' ')
			data.i++;
		data.state = GENERAL;
		data.c = check_token(str,data.i);
		res = check_if_env(envs, &data, str, head);
		if(res == 1 || res == 2)
		{
			if(res == 2)
				break;
			continue; 
		}
		if(data.c == DREDIR_OUT || data.c == HERE_DOC)
		{
			data.t = data.c;
			if(data.c == DREDIR_OUT)
				data.c = '>';
			else
				data.c = '<';
			data.tmp = g_collector(3, envs);
			data.tmp[0] = data.c;
			data.tmp[1] = data.c;
			data.tmp[2] = 0;
			head = ft_save(data.tmp,head,data.t,0,data.state, envs);
			data.i += 2;
			continue;
		}
		else if(data.c == -1)
		{
			data.t = data.c;
			data.tmp = g_collector(data.len + 1, envs);
			data.j = 0;
			while(data.c == -1 && str[data.i])
			{
				data.tmp[data.j++] = str[data.i++];
				data.c = check_token(str,data.i);
				if(data.c != -1 || str[data.i] == 0)
				{
					data.tmp[data.j] = '\0';
					head = ft_save(data.tmp,head,data.t,0,data.state, envs);
					if(data.c != -1)
						data.i--;
					break;
				}
			}
			if(str[data.i] == 0)
				break;
			if(str[data.i + 1] == ' ')
			{
				head = ft_save(data.tmp,head,WHITE_SPACE,1,data.state, envs);
				data.i++;
			}
		}
		else if(data.c == 34 || data.c == 39)
		{
			head = ft_save(str,head,data.c,str[data.i],data.state, envs);
			data.i++;
			data.j = 0;
			data.tmp = g_collector(data.len + 1, envs);
			data.t = data.c;
			if(str[data.i] == data.c)
			{
				head = ft_save(str,head,data.c,str[data.i],data.state, envs);
				data.i++;
				continue;
			}
			while(str[data.i] && str[data.i] != data.t)
			{
				data.tmp[data.j++] = str[data.i++];
				data.c = check_token(str,data.i);
				if(data.c == data.t)
				{
					if(data.c == 34)
						data.state = INDQUOTE;
					else
						data.state = INQUOTE;
					data.tmp[data.j] = '\0';
					head = ft_save(data.tmp,head,-1,0,data.state, envs);
					if(data.c == data.t)
					{
						data.state = GENERAL;
						head = ft_save(str,head,data.c,data.c,data.state, envs);
					} 
					break;
				}
			}
			if(str[data.i] == 0)
				break;
			if(str[data.i + 1] == ' ')
			{
				head = ft_save(data.tmp,head,WHITE_SPACE,1,data.state, envs);
				data.i++;
			}
		}
		else
			head = ft_save(str,head,data.c,str[data.i],data.state, envs);
		data.i++;
	}
	
	return(head);
}
