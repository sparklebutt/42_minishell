#include "minishell.h"

int	ft_count_exp_array(const char *s)
{
	int	count;
	int i;

	i = 0;
	count = 0;
	if (*s == '\0')
		return (1);
	while (*s != '\0')
	{
		// printf("START CHAR = %c\n", *s);
		if (*s == '\'')
		{
			// printf("\t\tstepped into single quotes\n");
			s++;
			i++;
			if (*s == '\'')
				count++; // how the f does this work?
			while (*s && *s != '\'')
			{
				// printf("\tsingle quotes = %c\n", *s);
				i++;
				s++;
			}
			s++;
			count++;
		}
		else if (*s == '"')
		{
			// printf("\t\tstepped into double quotes\n");
			s++;
			i++;
			if (*s == '"')
				count++;
			while (*s && *s != '"')
			{
				// printf("\t\tdouble quotes = %c\n", *s);
				s++;
				i++;
			}
			s++;
			count++;    
		}
		else
		{
			if (*s + 1 != '\0' && *s == '$')
			{
				// printf("\t\t\tdollar = %c\n", *s);
				s++;
			}    
			while (*s && *s != '\'' && *s != '"' && *s != '$')
			{
				// printf("\t\t\tno quotes = %c\n", *s);
				s++;
			}
				
			count++;       
		}
		// printf("count = %d\n", count);
	}
	return (count);
}

static int	ft_count_sub_len(const char *s, int sublen)
{
	int	save;
	int quotes;

	save = sublen;
	sublen = 0;
	quotes = 0;
	if (!s)
		return (0);
	if (s[save] == '\'')
	{
		save++;
		sublen++;
		while (s[save] && s[save] != '\'')
		{
			save++;
			sublen++;
		}
		save++;
		sublen++;
	}
	else if (s[save] == '"')
	{
		save++;
		sublen++;
		while (s[save] && s[save] != '"')
		{
			save++;
			sublen++;
		}
		save++;
		sublen++;
	}
	else
	{
		if (s[save + 1] != '\0' && s[save] == '$')
		{
			save++;
			sublen++;
		}
		if (s[save + 1] == '\0' && s[save] == '$')
			return (++sublen);
		while (s[save] && s[save] != '\'' && s[save] != '"' && s[save] != '$')
		{
			save++;
			sublen++;
		}
	}
	return (sublen);
}

char	**free_loop(char **arr, int index)
{
	while (--index)
		arr[index] = free_string(arr[index]);
	free(arr);
	return (NULL);
}
/*~~removing tokens causes issues qith quick tests , i dont know why yet~~*/
char	**ft_split_expansions(t_tokens *tokens, char const *s) //
{
	unsigned long int	i;
	int					index;
	char				**array;
	int					sublen;
	(void)tokens;
	int size_r;

	size_r = 0;
	i = 0;
	index = 0;
	array = NULL;
	if (s == NULL)
		return (NULL);
	size_r = ft_count_exp_array(s);
	// printf("size_r = %d\n", size_r);
	array = ft_calloc(size_r + 1, sizeof(char *)); // MALLOCED VARIABLE
	if (array == NULL)
		return (NULL);
	while (i < ft_strlen(s))
	{
		if (s[i] == '\0')
			return (array);
		sublen = ft_count_sub_len(s, i);
		array[index] = ft_substr(s, i, sublen);
		// printf("\nsublen = %d\n", sublen);
		if (!array[index])
			return (free_loop(array, index));
		// printf("token = %s\n", array[index]);
		i = i + sublen;
		index++;
	}
	array[index] = NULL;
	return (array);
}
