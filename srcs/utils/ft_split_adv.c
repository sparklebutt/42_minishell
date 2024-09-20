/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_adv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:10:33 by araveala          #+#    #+#             */
/*   Updated: 2024/09/20 09:43:53 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*this is baisicicaly split excepet it ignores the delimeter
inside quotes. Quotes signify a full string therefore we need
any and all spaces inside them */
int	fancy_strlen(char const *s, char c, int i)
{
	while (s[i] && s[i] != c)
	{
		if (s[i] == '"')
			fancy_loop(s, &i, '"');
		else if (s[i] == '\'')
			fancy_loop(s, &i, '\'');
		else if (is_char_redir(s[i]) > 0)
		{
			if (i == 0)
			{
				if (is_char_redir(s[i + 1]) > 0)
					return (2);
				else
					return (1);
			}
			return (i);
		}
		else if (i > 0 && s[i - 1] != 32 && s[i + 1]
			&& s[i + 1] != 32 && s[i] == '|')
			return (i);
		if (s[i] && s[i] != c)
			i++;
	}
	return (i);
}

// void	stupid_function_2(int *words, int *i, const char *s, char c)
// {
// 	(*words)++;
// 	(*i) += fancy_strlen(s, c, *i) - (*i);
// 	if (s[*i] && is_char_redir(s[*i - 1]) > 0 && is_char_redir(s[*i - 2]) == 0)
// 		(*i)--;
// 	else if (s[*i] && is_char_redir(s[*i - 1]) > 0
// 		&& is_char_redir(s[*i - 2]) > 0)
// 		(*i) -= 2;
// }

/*~~ leave commented code in here, i will finish this soon,
it got a bit late, attempt to increase word count based on
having no spaces but having redirects non the less, 
will add pipes also~~*/
size_t	total_words_c(char const *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	if (ft_strlen(s) == 1)
		return (1);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			stupid_if_statement(s, &i);
		else if (is_char_redir(s[i]) > 0)
		{
			if (s[i + 1] && is_char_redir(s[i + 1]) > 0)
				i++;
			lol(&words, &i);
		}
		else if (s[i] == '|')
			lol(&words, &i);
		else if (s[i] == '$' || s[i] != c)
			stupid_function_2(&words, &i, s, c);
	}
	return (words);
}

void	check_check_check(int *flag, int *x, const char *s, int i)
{
	if (*flag == 0 && (*x) > 1 && is_char_redir(s[i]) > 0)
	{
		(*x)--;
		if (*x > 1 && s[1] && is_char_redir(s[i + 1]) > 0)
			(*x)--;
		(*flag)++;
	}
	else if (*flag == 1)
	{
		(*x)++;
		(*flag)--;
	}
}

// int	get_word_len(int *check, int *x)
// {
// 	int	word_len;

// 	word_len = 0;
// 	if (*check > *x)
// 		word_len = (*check) - (*x);
// 	else
// 		word_len = (*x) - (*check);
// 	return (word_len);
// }

// void	init_adv_loop(t_temps *tmp)
// {
// 	tmp->word_len = 0;
// 	tmp->i = 0;
// 	tmp->flag = 0;
// 	tmp->x = 0;
// 	tmp->check = 0;
// }

// char	*stupid_function(size_t *word, t_temps *tmp, const char *s)
// {
// 	(*word)++;
// 	lol(&tmp->i, &tmp->x);
// 	return (ft_substr(s, tmp->word_len, 1));
// }

char	**adv_loop(char **array, const char *s, size_t total_words,
	t_temps *tmp)
{
	size_t		word;

	word = 0;
	init_adv_loop(tmp);
	while (s[tmp->i] != '\0' && word < total_words)
	{
		while (s[tmp->i] == 32)
			lol(&tmp->i, &tmp->x);
		tmp->x += tmp->word_len;
		tmp->check = fancy_strlen(s, 32, tmp->i);
		check_check_check(&tmp->flag, &tmp->x, s, tmp->i);
		tmp->word_len = get_word_len(&tmp->check, &tmp->x);
		array[word] = ft_substr(s, tmp->i, tmp->word_len);
		if (array[word] == NULL)
			return (free_array(array), NULL);
		tmp->i += ft_strlen(array[word]);
		if (s[tmp->word_len] == '|' && s[tmp->i])
			array[word] = stupid_function(&word, tmp, s);
		if (word < total_words)
			word++;
	}
	array[word] = NULL;
	return (array);
}

/*~~ split string but do not remove spaces if inside quotes to input
into tokesn array we are missing special cases where there are no spaces
yet special symbols do exist eg hello>world>spagett OR
echo hello>banana_file|cat>spaghetti, total_words_c will also have to take
all of this into consideration, due to atleast 1 extra use of the fucn*/
char	**ft_split_adv(char const *s, char c, t_data *data)
{
	char	**array;
	int		word_len;
	int		x;
	size_t	total_words;

	x = 0;
	if (s[0] == '|')
		return (not_perror("syntax error", NULL, "unexpected token\n"), NULL);
	total_words = total_words_c(s, c) + 1;
	(void)data;
	word_len = 0;
	array = NULL;
	if (!*s || !s)
		return (NULL);
	array = (char **)ft_calloc(sizeof(char *), total_words);
	if (!s || !array)
		return (NULL);
	if (total_words == 2)
	{
		array[0] = ft_substr(s, 0, ft_strlen(s) + 1);
		array[1] = NULL;
		return (array);
	}
	array = adv_loop(array, s, total_words, data->tmp);
	return (array);
}
