/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:22:00 by marvin            #+#    #+#             */
/*   Updated: 2025/05/15 18:22:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int ft_redirect_in(t_parsing *head)
{
    int fd;

    if(!head)
        return(2);
    head = head->next;
    while(head)
    {
        if(head->type == WORD)
            break;
        head = head->next;
    }
    fd = open(head->content, O_WRONLY | O_CREAT | O_TRUNC ,0644);
    if(fd == -1)
    {
        printf("error\n");
        return(2);
    }
    write(fd,"hello",5);
    return(0);
}