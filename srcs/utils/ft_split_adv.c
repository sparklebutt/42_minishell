/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_adv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:10:33 by araveala          #+#    #+#             */
/*   Updated: 2024/09/18 15:44:56 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*this is baisicicaly split excepet it ignores the delimeter
inside quotes. Quotes signify a full string therefore we need
any and all spaces inside them */
int	fancy_strlen(char const *s, char c, int i)
{
	int	test;

	test = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '"')
			fancy_loop(s, &i, '"');
		else if (s[i] == '\'')
			fancy_loop(s, &i, '\'');
		else if (is_char_redir(s[i]) > 0)
		{
			i++;
			test = is_char_redir(s[i]);
			if (test > 0)
				return (i += 1);
			return (i);
		}
		i++;
	}
	return (i);
}

/*~~ leave commented code in here, i will finish this soon,
it got a bit late, attempt to increase word count based on
having no spaces but having redirects non the less, 
will add pipes also~~*/
size_t	total_words_c(char const *s, char c)
{
	int	words;
	int	i;
	int	test;

	test = 0;
	words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			// stupid_if_statement(s, &i);
			if (s[i] == '"' && i++)
			{
				while (s[i] && s[i] != '"')
					i++;
			}
			else if (s[i] == '\'' && i++)
			{
				while (s[i] && s[i] != '\'')
					i++;
			}
			i++;
		}
		else if (is_char_redir(s[i]) > 0)
		{
			test++;
			i += is_char_redir(s[i]);
		}
		else if (s[i] == '$' || s[i] != c)
		{
			words++;
			i += fancy_strlen(s, c, i) - i;
		}
	}
	return (words + test);
}

char	**adv_loop(char **array, const char *s, int x, char c)
{
	int			word_len;
	size_t		word;
	int		i;
	size_t		total_words;

	word_len = 0;
	word = 0;
	i = 0;
	total_words = total_words_c(s, c) + 1;
	while (s[i] != '\0' && word < total_words)
	{
		while (s[i] == c)
			lol(&i, &x);
		x += word_len;
		word_len = fancy_strlen(s, c, i) - x;
		array[word] = ft_substr(s, i, word_len);
		if (array[word] == NULL)
			return (free_array(array), NULL);
		i += ft_strlen(array[word]);
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
	int	x;
	size_t	testing;

	x = 0;
	testing = total_words_c(s, c);
	(void)data;
	word_len = 0;
	array = (char **)ft_calloc(sizeof(char *), total_words_c(s, c) + 1);
	if (!s || !array)
		return (NULL);
	array = adv_loop(array, s, x, c);
	return (array);
}
