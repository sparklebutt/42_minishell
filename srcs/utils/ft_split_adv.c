/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_adv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:10:33 by araveala          #+#    #+#             */
/*   Updated: 2024/09/19 19:17:23 by araveala         ###   ########.fr       */
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
			printf("\ts[i] = %c\n", s[i]);
			printf("\ts[i + 1] = %c\n", s[i + 1]);
			if (i == 0)
			{
				printf("first location is 0!!! %c\n", s[i+1]);
				return (i + 1);
			}
			else if (is_char_redir(s[i + 1]) == 0)
			{
				printf("next one IS a redir %c\n", s[i+1]);
				return (i);
			}
			else if (is_char_redir(s[i + 1]) > 0)
				return (i + 1);

		}
		else if (i > 0 && s[i - 1] != 32 && s[i + 1] && s[i + 1] != 32 && s[i] == '|')
			return(i); //=1
		i++;
	}
	printf("fancy string len returns %c\n", s[i]);
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

	words = 0;
	i = 0;
	if (ft_strlen(s) == 1)
		return (1);
	while (s[i] != '\0')
	{
		printf("char 1 = %c\n", s[i]);
		if (s[i] == c)
		{
			printf("\tstepping in here!! found space\n");
			stupid_if_statement(s, &i);
		}
		else if (is_char_redir(s[i]) > 0)
		{
			printf("\t\tchar 2 = %c\n", s[i]);
			words++;
			printf("\t\twords = %d\n", words);
			if (s[i + 1] && is_char_redir(s[i + 1]) > 0)
			{
				i++;
				printf("\t\tchar 3 = %c\n", s[i]);
			}
			i += is_char_redir(s[i]);
			printf("\t\tchar 4 = %c\n", s[i]);
		}
		else if (s[i] == '|')
		{
			words++;
			printf("\t\t\twords = %d\n", words);
			i += 1;
			printf("\t\t\tchar 5 = %c\n", s[i]);
		}
		else if (s[i] == '$' || s[i] != c)
		{
			words++;
			printf("\t\t\t\twords = %d\n", words);
			printf("\t\t\t\tchar 6 = %c\n", s[i]);
			i += fancy_strlen(s, c, i) - i;
			printf("\t\t\t\tchar 7 = %c\n", s[i]);
		}
	}
	return (words);
}

char	**adv_loop(char **array, const char *s, int x, char c)
{
	int			word_len;
	size_t		word;
	int			i;
	size_t		total_words;

	word_len = 0;
	word = 0;
	i = 0;
	total_words = total_words_c(s, c) + 1;
	printf("totla words = %zu\n", total_words);
	while (s[i] != '\0' && word < total_words)
	{
		printf("THIS IS THE CHAR = %c\n", s[i]);
		while (s[i] == c)
			lol(&i, &x);
		x += word_len;
		printf("\tlength of the last word %d\n", x);
		word_len =  fancy_strlen(s, c, i) - x;
		printf("\tcurrent word's length %d\n", word_len);
		//printf("what is word? %zu\n", word);
		array[word] = ft_substr(s, i, word_len);
		printf("\tarray[%zu] = %s\n", word, array[word]);
		if (array[word] == NULL)
			return (free_array(array), NULL);
		//x += word_len;
		i += ft_strlen(array[word]);
		printf("\tthe next char is %c\n", s[i]);
		//word_len = fancy_strlen(s, c, i) - x;
		 /*if (s[i] && is_char_redir(s[i]) > 0)
		{
			word++;
			//i++;
			x++;
			array[word] = ft_substr(s, i, word_len);
			printf("array[%zu] = %s\n", word, array[word]);
			i++;
			printf("i = %d and s[i] = %c\n", i, s[i]);
		}*/
		if (s[word_len] == '|' && s[i])
		{
			word++;
			i++;
			x++;
			array[word] = ft_substr(s, word_len, 1);
		}
		//if (word < total_words)
		word++;
	}
	print_arr(array, "the shitter");
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
	size_t	testing;

	x = 0;
	testing = total_words_c(s, c);
	//printf("words = %zu\n", testing);
	(void)data;
	word_len = 0;
	array = NULL;
	if (!*s || !s)
		return (NULL);
	array = (char **)ft_calloc(sizeof(char *), testing + 1);
	if (!s || !array)
		return (NULL);
	if (testing == 1)
	{
		array[0] = ft_substr(s, 0, ft_strlen(s) + 1); // if this throws a fit, remove +1
		array[1] = NULL;
		return (array);
	}
	array = adv_loop(array, s, x, c);
	return (array);
}
