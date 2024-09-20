/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_adv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:10:33 by araveala          #+#    #+#             */
/*   Updated: 2024/09/20 06:58:37 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*this is baisicicaly split excepet it ignores the delimeter
inside quotes. Quotes signify a full string therefore we need
any and all spaces inside them */
int	fancy_strlen(char const *s, char c, int i)
{
	// printf("------------- FANCY_STRLEN -------------\n");
	while (s[i] && s[i] != c)
	{
		// printf("\tCHECK THIS s[%d] = %c\n", i, s[i]);
		if (s[i] == '"')
			fancy_loop(s, &i, '"');
		else if (s[i] == '\'')
			fancy_loop(s, &i, '\'');
		else if (is_char_redir(s[i]) > 0)
		{
			// printf("\tIT IS A REDIRECT!\n");
			// printf("\twhat is the next ones[i + 1] = %c\n", s[i + 1]);
			if (i == 0)
			{
				// printf("\t\tredir is first char, returning word\n");
				// printf("\t\tnew s[%d] is %c\n", i, s[i+1]);
				if (is_char_redir(s[i + 1]) > 0)
				{
					// printf("\t\tA next char is a redir, return 2\n");
					return (2);
				}
				else
				{
					// printf("\t\tA next char is NOT redir, return 1\n");
					return (1);
				}
			}
			return (i);
		}
		else if (i > 0 && s[i - 1] != 32 && s[i + 1] && s[i + 1] != 32 && s[i] == '|')
			return(i); //=1
		// printf("\tCHECK THIS s[%d] = |%c|\n", i, s[i]);
		if (s[i] && s[i] != c)
			i++;
	}
	// printf("\tSTRING ENDED, final char is s[%d] = %c\n", i - 1, s[i - 1]);
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
	// printf("------------- TOTAL_WORDS_C -------------\n");
	while (s[i] != '\0')
	{
		// printf("\tCHECK THIS s[i] = %c\n", s[i]);
		if (s[i] == c)
		{
			// printf("\t\twe found a space!\n");
			stupid_if_statement(s, &i);
		}
		else if (is_char_redir(s[i]) > 0)
		{
			// printf("\tIT IS A REDIRECT!\n");
			words++;
			// printf("\twords = %d\n", words);
			if (s[i + 1] && is_char_redir(s[i + 1]) > 0)
			{
				// printf("\t\tTHE NEXT ONE IS ALSO A REDIRECT!\n");
				i++;
				// printf("\tNEW s[i] = %c\n", s[i]);
			}
			i++;
			// printf("\tNEW s[i] = %c\n", s[i]);
		}
		else if (s[i] == '|')
		{
			words++;
			// printf("\twords = %d\n", words);
			i++;
			// printf("\tNEW s[i] = %c\n", s[i]);
		}
		else if (s[i] == '$' || s[i] != c)
		{
			words++;
			// printf("\twords = %d\n", words);
			// printf("\tBEFORE FANCY_STRLEN s[i] = %c\n", s[i]);
			i += fancy_strlen(s, c, i) - i;
			if (s[i] && is_char_redir(s[i - 1]) > 0 && is_char_redir(s[i - 2]) == 0)
				i--;
			else if (s[i] && is_char_redir(s[i - 1]) > 0 && is_char_redir(s[i - 2]) > 0) // maybe not needed
				i-=2;
			// printf("\twords = %d\n", words);
			// printf("\tAFTER FANCY_STRLEN s[i] = %c\n", s[i]);
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
	int			check;
	int flag;

	word_len = 0;
	word = 0;
	i = 0;
	flag = 0;
	total_words = total_words_c(s, c) + 1;
	// printf("------AAAAA------ ADV_LOOP -------AAAAA-----\n");
	// printf("total words = %zu\n", total_words);
	while (s[i] != '\0' && word < total_words)
	{
		// printf("THIS IS THE CHAR = %c\n", s[i]);
		while (s[i] == c)
			lol(&i, &x);
		x += word_len;
		// printf("\tlengt/h of the last word %d\n", x);
		check = fancy_strlen(s, c, i);
		// printf("fancy_strlen = %d\n", check);
		// printf("x = %d\n", x);
		if (flag == 0 && x > 1 && is_char_redir(s[i]) > 0)
		{
			// printf("DOES IT STEP INTO HERE??????\n");
			x--;
			if (x > 1 && s[1] && is_char_redir(s[i + 1]) > 0)
				x--;
			flag++;
		}
		else if (flag == 1)
		{
			x++;
			flag--;
		}
		if (check > x)
		{
			// printf("word_len A\n");
			word_len =  check - x;
		}	
		else
		{
			// printf("word_len B\n");
			word_len =  x - check;
		}	
		// printf("\tcurrent word's length %d\n", word_len);
		array[word] = ft_substr(s, i, word_len);
		// printf("\tarray[%zu] = %s\n", word, array[word]);
		if (array[word] == NULL)
			return (free_array(array), NULL);
		i += ft_strlen(array[word]);
		// printf("\tthe next char is %c\n", s[i]);
		if (s[word_len] == '|' && s[i])
		{
			word++;
			i++;
			x++;
			array[word] = ft_substr(s, word_len, 1);
		}
		if (word < total_words)
			word++;
	}
	// print_arr(array, "the shitter");
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
