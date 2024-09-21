/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:12:32 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/21 17:53:01 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_str(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] == str2[i])
		i++;
	if (str1[i] > str2[i])
		return (1);
	return (0);
}

char	*ft_strtrim_front(char *s1, char set)
{
	int		i;
	char	*trimmed_str;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(&s1[i], set))
	{
		if (s1[i] == '\0')
			return (NULL);
		i++;
	}
	trimmed_str = ft_substr(s1, 0, i - 1);
	if (trimmed_str == NULL)
		return (NULL);
	return (trimmed_str);
}

void	dollar_counter(char *string, t_tokens *tokens)
{
	int	i;

	i = 0;
	tokens->dollar_count = 0;
	while (string[i])
	{
		if (string[i] == '$')
			tokens->dollar_count++;
		i++;
	}
}

int	check_next(char *str, size_t len)
{
	if (str == NULL && len == 1)
		return (1);
	return (0);
}

int	null_check(char *str1, t_env *str2, char *str3)
{
	if (str1 == NULL || str2 == NULL)
	{
		if (str1 == NULL)
			ft_printf("ENVS KEY NULL \n");
		else if (str2 == NULL)
			ft_printf("ENVS IS NULL\n");
		return (0);
	}
	if (str3 == NULL)
	{
		ft_printf("STRING IS NULL");
		return (-1);
	}
	return (1);
}
