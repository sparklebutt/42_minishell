/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:18:51 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/21 16:00:26 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	fancy_strlen_a(char const *s, char c, int i)
{
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

size_t	total_words(char const *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else if (s[i] != c)
		{
			words++;
			i += fancy_strlen_a(s, c, i) - i;
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

char	**malloc_array(size_t total_words, int *word, int *i)
{
	char	**array;

	(*i) = 0;
	(*word) = 0;
	array = malloc(sizeof(char *) * (total_words + 1));
	if (!array)
		return (NULL);
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		word;
	int		word_len;
	int		i;

	array = malloc_array(total_words(s, c), &word, &i);
	if (!s | !array)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			word_len = fancy_strlen_a(s, c, i) - i;
			array[word] = ft_substr(s, i, word_len);
			if (array[word] == NULL)
				return (free_array_if(array));
			word++;
			i += word_len;
		}
	}
	array[word] = NULL;
	return (array);
}
