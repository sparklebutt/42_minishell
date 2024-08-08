/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_adv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:10:33 by araveala          #+#    #+#             */
/*   Updated: 2024/08/08 16:20:56 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*~~ this is baisicicaly split excepet it ignores the delimeter inside quotes.
quotes signify a full string therefore we need any and all spaces inside them ~~*/
static int	fancy_strlen(char const *s, char c, int i)
{
	while (s[i] && s[i] != c)
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
		}
		i++;
	}
	return (i);
}

size_t	total_words_c(char const *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			if (s[i] == '"' && i++)
			{
				while (s[i] && s[i] != '"')
					i++;
			}
			else if (s[i] == '\'')
			{
				while (s[i] && s[i] != '\'' && i++)
					i++;
			}
			i++;
		}
		else if (s[i] != c && words++)
			i += fancy_strlen(s, c, i) - i; // had words++; seperate
	}
	return (words);
}

static char	**free_array_if(char **array)
{
	int	word;

	word = 0;
	while (array[word] != NULL)
		free(array[word++]);
	free(array);
	return (NULL);
}

char	**ft_split_adv(char const *s, char c)
{
	size_t	i;
	char	**array;
	int		word;
	int		word_len;

	i = 0;
	word = 0;
	array = (char **)ft_calloc(sizeof(char *), (total_words_c(s, c) + 1));
	if (!s || !array)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		word_len = fancy_strlen(s, c, i) - i;
		array[word] = ft_substr(s, i, word_len);
		if (array[word] == NULL)
			return (free_array_if(array));
		i += ft_strlen(array[word]);
		word++;
	}
	array[word] = NULL;
	return (array);
}
