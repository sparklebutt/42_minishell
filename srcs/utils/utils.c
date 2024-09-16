/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:12:32 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/13 13:14:03 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_str(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] == str2[i])
		i++;
	if (str1[i] > str2[i])
		return (1);
	return (0);
}

char	*ft_strtrim_front(char *s1, char set)
{
	int		i;
	char	*trimmed_str;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(&s1[i], set))
	{
		if (s1[i] == '\0')
				return (NULL);
		i++;
	}
	trimmed_str = ft_substr(s1, 0, i - 1);
	if (trimmed_str == NULL)
		return (NULL);
	return (trimmed_str);
}
