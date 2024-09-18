/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_loopers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:08:22 by araveala          #+#    #+#             */
/*   Updated: 2024/09/18 15:05:23 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_echo_loop(char **args, int *x, int *i)
{
	char	*temp;

	(*x) = ft_strlen(args[*i]) + 2;
	temp = ft_calloc(*x, sizeof(char));
	if (temp == NULL)
		return (not_perror("echo", NULL, "malloc fail"), -1);
	temp[0] = 0x06;
	ft_strcpy(temp + 1, args[*i]);
	free_string(args[*i]);
	args[*i] = ft_strdup(temp);
	free_string(temp);
	(*i)++;
	(*x) = 0;
	return (0);
}
