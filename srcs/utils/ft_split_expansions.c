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
        if (*s == '\'')
        {
            s++;
            i++;
            if (*s == '\'')
                count++; // how the f does this work?
            while (*s && *s != '\'')
            {
                i++;
                s++;
            }
            count++;
        }
        else if (*s == '"')
        {
            s++;
            i++;
            if (*s == '"')
                count++;
            while (*s && *s != '"')
            {
                s++;
                i++;
            }
            count++;    
        }
        else
        {
            while (*s && *s != '\'' && *s != '"')
                s++;
            count++;       
        }
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
        sublen++;
    }
    else
    {
        while (s[save] && s[save] != '\'' && s[save] != '"')
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
		free_string(arr[index]);
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
	array = ft_calloc(size_r + 1, sizeof(char *)); // MALLOCED VARIABLE
	if (array == NULL)
		return (NULL);
    //array[size_r] = NULL;
	while (i < ft_strlen(s)) //(index < size_r)//
	{
		if (s[i] == '\0')
   			return (array);
 		sublen = ft_count_sub_len(s, i);
		array[index] = ft_substr(s, i, sublen);
       // printf("\n\t\tindex [%d] = %s\n", index, array[index]);
		if (!array[index])
			return (free_loop(array, index));
		i = i + sublen;
		index++;
	}
    //printf("whats at our index = %d and what should it not be over = %d\n", index, size_r);
    array[index] = NULL;
	return (array);
}
