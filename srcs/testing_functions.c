/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:26:41 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/19 17:12:22 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_arr(char **array, char *array_name)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%s[%d] = |%s|\n", array_name, i, array[i]);
		i++;
	}
	return (0);
}
