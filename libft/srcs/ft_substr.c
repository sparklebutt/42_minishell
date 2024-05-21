/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:16:36 by vkettune          #+#    #+#             */
/*   Updated: 2024/01/03 05:49:45 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t l)
{
	char	*substr;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (s_len < start)
		return (ft_strdup(""));
	if (l + start > s_len)
		l = s_len - (size_t)start;
	substr = (char *)malloc(sizeof(char) * (l + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, l + 1);
	return (substr);
}
