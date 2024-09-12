/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_adv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:10:33 by araveala          #+#    #+#             */
/*   Updated: 2024/09/12 19:02:50 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*~~ this is baisicicaly split excepet it ignores the delimeter inside quotes.
quotes signify a full string therefore we need any and all spaces inside them ~~*/
static int	fancy_strlen(char const *s, char c, int i, t_data *data)
{
	int test;
	
	if (data->i == 100)//// remove me later
		printf("A");
	test = 0;
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
		else if (is_char_redirect(s[i]) > 0)
		{
			i++;
			test = is_char_redirect(s[i]);
			if (test > 0)
				return (i += 1);
			return(i);
		}
		i++;
	}
	return (i);
}

/*~~ leave commented code in here, i will finish this soon, it got a bit late, attempt
to increase word count based on having no spaces but having redirects non the less, 
will add pipes also~~*/
size_t	total_words_c(char const *s, char c, t_data *data)
{
	int	words;
	int	i;
	int test;

	test = 0;
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
			else if (s[i] == '\'' && i++)
			{
				while (s[i] && s[i] != '\'')
					i++;
			}
			i++;
		}
		else if (is_char_redirect(s[i]) > 0)
		{
			test++;
			i += is_char_redirect(s[i]);
		}
		else if (s[i] == '$')
		{
			words++;
			i += fancy_strlen(s, c, i, data) - i; // - 1?		
		}
		else if (s[i] != c)
		{
			words++;
			i += fancy_strlen(s, c, i, data) - i;
		}
	}
	return (words + test);
}

static char	**free_array_if(char **array)
{
	int	word;

	word = 0;
	while (array[word] != NULL)
		free_string(array[word++]);
	free(array);
	return (NULL);
}

/*~~ split string but do not remove spaces if inside quotes to input into tokesn array
we are missing special cases where there are no spaces yet special symbols do exist
eg hello>world>spagett OR echo hello>banana_file|cat>spaghetti, total_words_c will also have
to take all of this into consideration, due to atleast 1 extra use of the fucntion~~*/
char	**ft_split_adv(char const *s, char c, t_data *data) //lets send it a 0 for i
{
	size_t	i;
	size_t	x = 0;
	char	**array;
	size_t		word;
	int		word_len;
	size_t testing = total_words_c(s, c, data);

	i = 0;
	word = 0;
	word_len = 0;
	array = (char **)ft_calloc(sizeof(char *), testing + 1);//(total_words_c(s, c) + 1)); // MALLOCED VARIABLE
	if (!s || !array)
		return (NULL);
	while (s[i] != '\0' && word < testing) //total_words_c(s, c)) // 
	{
		while (s[i] == c)
		{
			i++;
			x++;
		}
		x+= word_len;
		word_len = fancy_strlen(s, c, i, data) - x;		
		array[word] = ft_substr(s, i, word_len);
		if (array[word] == NULL)
			return (free_array_if(array));
		i += ft_strlen(array[word]);
		word++;
	}
	array[word] = NULL;
	//printf("zzzzzzzzzzzzzzzzzzzz\n");
	/*int p = 0;
	while (array[p] != NULL)
	{
		printf("array[%d] = %s\n", p, array[p]);
		p++;
	}*/
		
	return (array);
}
