/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 04:41:19 by vkettune          #+#    #+#             */
/*   Updated: 2024/01/03 05:49:14 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dest, const char *restrict src, size_t l)
{
	size_t	s_len;
	size_t	d_len;

	s_len = ft_strlen(src);
	d_len = ft_strlen(dest);
	if (l < d_len || l == 0)
		return (s_len + l);
	else
	{
		dest = &dest[d_len];
		ft_strlcpy(dest, src, l - d_len);
		return (d_len + s_len);
	}
}
