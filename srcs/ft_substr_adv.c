/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_adv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:28:39 by araveala          #+#    #+#             */
/*   Updated: 2024/09/10 20:55:28 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	*ft_substr_adv(t_data *data, char const *s, unsigned int start, size_t l)
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
	if (data->glue == true)
		substr = (char *)malloc(sizeof(char) * (l + 2));
	else
		substr = (char *)malloc(sizeof(char) * (l + 1));	
	if (!substr)
		return (NULL);
	if (data->glue == true)
	{
		ft_strlcpy(substr, s + start, l + 2);
		substr[ft_strlen(substr - 1)] = '\x06';
	}
	else
		ft_strlcpy(substr, s + start, l + 1);
	return (substr);
}*/


// can this be removed? new, by vilja
