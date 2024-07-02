/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_adv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:10:33 by araveala          #+#    #+#             */
/*   Updated: 2024/05/24 12:36:36 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int fancy_strlen(char const *s, char c, int i)
{
    while (s[i] != c && s[i])
	{
		if (s[i] == '"')//tis is to protect the spaces
		{
			i++;
			while (s[i] != '"')
				i++;
		}//
        i++;
	}
    return (i);
}

size_t  total_words_c(char const *s, char c)
{
    int words;
    int i;

    words = 0;
    i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == c)
		{
			if (s[i] == '"')//tis is to protect the spaces
			{
				i++;
				while (s[i] != '"')
					i++;
			}//
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

static char    **free_array_if(char **array)
{
    int word;

    word = 0;
    while (array[word] != NULL)
        free(array[word++]);
    free(array);
    return (NULL);
}

char    **ft_split_adv(char const *s, char c)
{
    char    **array;
    int     word;
    int     word_len;
    int     i;
	int x;

	x = 0;
    i = 0;
    word = 0;
    array = (char **)ft_calloc(sizeof(char *), (total_words_c(s, c) + 1));
    if (!s || !array)
        return (NULL);
    while (s[i])
    {

        if (s[i] == c)
		{
			i++;
			if (s[i] == '"')//tis is to protect the spaces
			{
				x++;
				while (s[i] != '"')
					x++;
			}//
		}
        else
        {
            word_len = fancy_strlen(s, c, i) - i + x;
            array[word] = ft_substr(s, i, word_len);
            if (array[word] == NULL)
                return (free_array_if(array));
            word++;
            i += word_len;
			x = 0;
        }
    }
    return (array);
}
