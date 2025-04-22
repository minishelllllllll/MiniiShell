/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:46:25 by himousta          #+#    #+#             */
/*   Updated: 2024/11/15 10:23:15 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	if (!s || fd < 0)
		return ;
	ft_strlen(s);
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
