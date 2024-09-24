/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_adv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:10:33 by araveala          #+#    #+#             */
/*   Updated: 2024/09/24 09:47:19 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fancy_strlen(char const *s, char c, int i)
{
	while (s[i] && s[i] != c)
	{
		if (s[i] && s[i] == '"')
			fancy_loop(s, &i, '"');
		else if (s[i] && s[i] == '\'')
			fancy_loop(s, &i, '\'');
		else if (is_char_redir(s[i]) > 0)
		{
			i++;
			while (s[i] && s[i] != c && is_char_redir(s[i]) > 0)
				i++;
			return (i);
		}
		else if (s[i] && s[i] == '|')
		{
			while (s[i] && s[i] != c && s[i] == '|')
				i++;
			return (i);
		}
		if (s[i] && s[i] != c)
			i++;
		if (s[i] && (s[i] == '|' || is_char_redir(s[i]) > 0))
			return (i);
	}
	return (i);
}

int	stupid_if_statement(const char *s, int *i, int *words, int *flag)
{
	if (s[*i] && s[*i] == '"')
	{
		fancy_loop(s, i, '"');
		(*words)++;
		(*flag) = 1;
		return (1);
	}
	else if (s[*i] && s[*i] == '\'')
	{
		fancy_loop(s, i, '\'');
		(*words)++;
		(*flag) = 1;
		return (1);
	}
	else if (s[*i] && is_char_redir(s[*i]) > 0)
	{
		(*i)++;
		while (s[*i] && is_char_redir(s[*i]) > 0)
			(*i)++;
		(*words)++;
		(*flag) = 1;
		return (1);
	}
	return (0);
}

size_t	total_words_c(char const *s, char c)
{
	int	words;
	int	i;
	int flag;

	words = 0;
	i = 0;
	flag = 0;
	if (ft_strlen(s) == 1)
		return (1);
	while (s[i] && s[i] != '\0')
	{
		if (s[i] && s[i] == c)
			i++;
		else if (stupid_if_statement(s, &i, &words, &flag) == 1)
			flag = 0;
		else if (s[i] && s[i] == '|')
		{
			while (s[i] && s[i] == '|')
				i++;
			words++;
		}
		else if (s[i] && s[i] != c)
			lol(&words, &i);
	}
	return (words);
}

char	**adv_loop(char **array, const char *s, size_t total_words,
	t_data *data)
{
	size_t		word;

	word = 0;
	init_adv_loop(data->tmp);

	while (s[data->tmp->i] != '\0' && word < total_words)
	{
		while (s[data->tmp->i] != '\0' && s[data->tmp->i] == 32)
			lol(&data->tmp->i, &data->tmp->x);
		if (s[data->tmp->i] == '\0')
			break ;
		data->tmp->x += data->tmp->word_len;
		data->tmp->check = fancy_strlen(s, 32, data->tmp->i);
		data->tmp->word_len = get_word_len(&data->tmp->check, &data->tmp->x);
		array[word] = ft_substr(s, data->tmp->i, data->tmp->word_len);
		if (array[word] == NULL)
			return (free_array(array), NULL);
		data->tmp->i += ft_strlen(array[word]);
		word++;
	}
	array[word] = NULL;
	data->tokens->array_count = word;
	return (array);
}

char	**ft_split_adv(char const *s, t_data *data)
{
	char	**array;
	int		x;

	x = 0;
	if (s[0] == '|')
		return (not_perror("syntax error", NULL, "unexpected token\n"), NULL);
	array = NULL;
	if (!*s || !s)
		return (NULL);
	array = (char **)ft_calloc(sizeof(char *), data->tokens->array_count + 1);
	if (!s || !array)
		return (NULL);
	array = adv_loop(array, s, data->tokens->array_count, data);
	return (array);
}
