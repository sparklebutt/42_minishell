/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:33:28 by araveala          #+#    #+#             */
/*   Updated: 2024/09/18 13:34:01 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lol(int *save, int *sublen)
{
	(*save)++;
	(*sublen)++;
}

int	ft_count_exp_array(const char *s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (*s == '\0')
		return (1);
	while (*s != '\0')
	{
		if (*s == '\'')
			s = exp_loop('\'', &i, s, &count);
		else if (*s == '"')
			s = exp_loop('"', &i, s, &count);
		else
		{
			if (*s + 1 != '\0' && *s == '$')
				s++;
			while (*s && *s != '\'' && *s != '"' && *s != '$')
				s++;
			count++;
		}
	}
	return (count);
}

static int	ft_count_sub_len(const char *s, int sublen)
{
	int	save;

	save = sublen;
	sublen = 0;
	if (!s)
		return (0);
	if (s[save] == '\'')
		sublen_loop('\'', &sublen, &save, s);
	else if (s[save] == '"')
		sublen_loop('"', &sublen, &save, s);
	else
	{
		if (s[save + 1] != '\0' && s[save] == '$')
			lol(&save, &sublen);
		if (s[save + 1] == '\0' && s[save] == '$')
			return (++sublen);
		while (s[save] && s[save] != '\'' && s[save] != '"' && s[save] != '$')
			lol(&save, &sublen);
	}
	return (sublen);
}

/*~~removing tokens causes issues qith quick tests , i dont know why yet~~*/
char	**ft_split_expansions(t_tokens *tokens, char const *s, int index)
{
	unsigned long int	i;
	char				**array;
	int					sublen;

	(void)tokens;
	i = 0;
	array = NULL;
	if (s == NULL)
		return (NULL);
	array = ft_calloc(ft_count_exp_array(s) + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	while (i < ft_strlen(s))
	{
		if (s[i] == '\0')
			return (array);
		sublen = ft_count_sub_len(s, i);
		array[index] = ft_substr(s, i, sublen);
		if (!array[index])
			return (free_loop(array, index));
		i = i + sublen;
		index++;
	}
	array[index] = NULL;
	return (array);
}
