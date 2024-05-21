/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 08:18:40 by vkettune          #+#    #+#             */
/*   Updated: 2024/01/03 05:48:13 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t l)
{
	size_t	i;

	i = 0;
	while (i < l)
	{
		if (((const char *)s)[i] == (char)c)
			return (&((void *)s)[i]);
		i++;
	}
	return (0);
}
