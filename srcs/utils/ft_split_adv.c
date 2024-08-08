/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_adv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:10:33 by araveala          #+#    #+#             */
/*   Updated: 2024/08/07 11:18:23 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fancy_strlen(char const *s, char c, int i)
{
	while (s[i] && s[i] != c)
	{
		if (s[i] == '"') // tis is to protect the spaces
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
		}
		else if (s[i] == '\'') // tis is to protect the spaces
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
			if (s[i] == '"') // tis is to protect the spaces
			{
				i++;
				while (s[i] && s[i] != '"')
					i++;
			}
			else if (s[i] == '\'') // tis is to protect the spaces newnew
			{
				i++;
				while (s[i] && s[i] != '\'')
					i++;
			}
			i++;
		}
		else if (s[i] != c)
		{
			words++;
			i += fancy_strlen(s, c, i) - i;
		}
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
	while (s[i] != '\0') // (i <= ft_strlen(s))//causing read error of 1 in valgrind
	{
		while (s[i] == c)
			i++;
//		printf("char = %c \n", s[i]);
//		printf("i before minus and i = %zu x = %d\n", i, x);
		word_len = fancy_strlen(s, c, i);// - i + x;
		array[word] = ft_substr(s, i, word_len);
//		printf("do we have a word her = %s\n", array[word]);
//		printf("do we have a word her = %s\n", s);						
		if (array[word] == NULL)
			return (free_array_if(array));
		i += ft_strlen(array[word]);//word_len;
//		printf("what is i now = %zu\n", i);
		word++;
	}
	array[word] = NULL; /*~~ this fixed a seg fault as now we have a null terminated array ~~*/
	return (array);
}

