/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 03:26:55 by hind              #+#    #+#             */
/*   Updated: 2025/07/04 03:26:55 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_redirect_out(t_parsing *head, t_var *data)
{
	int	fd;
	int	t;

	t = DREDIR_OUT;
	if (!head)
		return (2);
	if (head->type == REDIR_OUT)
		t = head->type;
	head = head->next;
	while (head)
	{
		if (head->type == WORD)
			break ;
		head = head->next;
	}
	if (!head || !head->content)
		return (2);
	if (t == REDIR_OUT)
		fd = open(head->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(head->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (2);
	data->out_file = fd;
	return (0);
}
