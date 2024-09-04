/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:39:13 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/30 09:46:21 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t l)
{
	char	c;
	char	*str;

	c = '\0';
	str = (char *)s;
	while (l)
	{
		(*str = c);
		*str = '\0';	
		str++;
		l--;
	}
}

/*void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, (size_t)n);
}*/