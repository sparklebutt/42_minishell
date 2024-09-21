/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_b_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:04:50 by araveala          #+#    #+#             */
/*   Updated: 2024/09/21 09:31:59 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_b.h"
#include <stdio.h>

void	*ft_calloc_b(int count)
{
	char	*storage_ptr;
	int		i;

	i = 0;
	printf("-------------- FT_CALLOC_B --------------\n");
	printf("count = %d\n", count);
	storage_ptr = malloc(sizeof(char) * count);
	if (storage_ptr == NULL)
		return (NULL);
	while (count > 0)
	{
		storage_ptr[i] = '\0';
		count--;
		i++;
	}
	return (storage_ptr);
}

void	free_string_b(char **string)
{
	if (*string != NULL)
	{
		free(*string);
		*string = NULL;
	}
}

int	nl_len(char *str, int redirect)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (*str != '\0')
	{
		if (*str == '\n' && redirect == 0)
			return (i);
		str++;
		i++;
	}
	if (redirect == 1)
		return (i);
	return (-1);
}

char	*ft_strdup_b(char *s1, int x)
{
	char	*new;
	int		len;
	int		i;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	printf("-------------- FT_STRDUP_B --------------\n");
	len = nl_len(s1, 1);
	printf("what is len? %d\n", len);
	printf("what is s1? |%s|\n", s1);
	new = ft_calloc_b(len + 1);
	if (new == NULL)
		return (NULL);
	while (s1[x] != '\0' && i <= (len))
	{
		new[i] = s1[x];
		i++;
		x++;
	}
	//free_string_b(&s1);
	return (new);
}

char	*ft_strjoin_b(char *s1, char *s2)
{
	char	*new;
	int		total_len;
	int		i;
	int		x;

	x = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	printf("-------------- FT_STRJOIN_B --------------\n");
	total_len = nl_len(s1, 1) + nl_len(s2, 1);
	printf("what is total len? %d\n", total_len);
	printf("what is s1? |%s|\n", s1);
	printf("what is s2? |%s|\n", s2);
	new = ft_calloc_b(total_len + 1);
	if (!new)
		return (NULL);
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[x] != '\0' && x < nl_len(s2, 1))
	{
		new[i] = s2[x];
		i++;
		x++;
	}
	return (new);
}
