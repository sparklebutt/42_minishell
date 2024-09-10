/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:16:36 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/10 15:43:53 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t l)
{
	char	*substr;
	size_t	s_len;

	substr = NULL;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		return (ft_strdup(""));
	if (l + start > s_len)
		l = s_len - (size_t)start;
	//substr = (char *)ft_calloc(sizeof(char) * (l + 1));
	substr = ft_calloc(l + 1, sizeof(char));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, l + 1);
	return (substr);
}
