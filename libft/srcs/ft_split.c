/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:18:51 by vkettune          #+#    #+#             */
/*   Updated: 2024/01/03 05:48:54 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fancy_strlen(char const *s, char c, int i)
{
	while (s[i] != c && s[i])
		i++;
	return (i);
}

size_t	total_words(char const *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else if (s[i] != c)
		{
			words++;
			i += fancy_strlen(s, c, i) - i;
		}
	}
	return (words);
}

char	**free_array_if(char **array)
{
	int	word;

	word = 0;
	while (array[word] != NULL)
		free(array[word++]);
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		word;
	int		word_len;
	int		i;

	i = 0;
	word = 0;
	array = (char **)ft_calloc(sizeof(char *), (total_words(s, c) + 1));
	if (!s || !array)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			word_len = fancy_strlen(s, c, i) - i;
			array[word] = ft_substr(s, i, word_len);
			if (array[word] == NULL)
				return (free_array_if(array));
			word++;
			i += word_len;
		}
	}
	return (array);
}
