/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:22:00 by marvin            #+#    #+#             */
/*   Updated: 2025/05/15 18:22:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int ft_here_doc(t_parsing *head)
{
    if(!head)
        return(2);
    head = head->next;
    int fd = open(head->content, O_CREAT | O_WRONLY );
    if(fd == -1)
    {
        printf("error\n");
        return(2);
    }
    write(fd,"hello",5);
    return(0);
}