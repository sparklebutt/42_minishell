/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:47:05 by vkettune          #+#    #+#             */
/*   Updated: 2024/01/03 05:49:35 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t l)
{
	size_t	h;
	size_t	n;
	size_t	n_len;
	char	*hay;

	h = 0;
	n_len = ft_strlen(needle);
	hay = (char *)haystack;
	if (needle[0] == '\0')
		return (hay);
	if (!l)
		return (NULL);
	while (hay[h] != '\0' && h < l)
	{
		n = 0;
		while ((needle[n] == hay[h + n]) && (h + n < l))
		{
			n++;
			if (needle[n] == '\0')
				return (&hay[h]);
		}
		h++;
	}
	return (0);
}
