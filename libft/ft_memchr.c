/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:10:10 by himousta          #+#    #+#             */
/*   Updated: 2024/11/13 22:34:19 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	while (((unsigned char *)s + i) && (i < n))
	{
		if (*((char *)s + i) == (char)c)
			return ((void *)s + i);
		i++;
	}
	return (0);
}
