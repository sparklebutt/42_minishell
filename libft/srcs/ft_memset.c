/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:41:17 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/30 09:46:34 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t l)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < l)
		str[i++] = (unsigned char)c;
	return (s);
}

/*void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*buffer;
	unsigned char	*return_p;

	return_p = b;
	buffer = b;
	while (len-- > 0)
	{
		*buffer = (unsigned char)c;
		buffer++;
		b++;
	}
	return (return_p);
}*/