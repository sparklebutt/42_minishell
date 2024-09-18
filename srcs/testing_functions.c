/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:26:41 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/18 22:26:44 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_arr(char **array, char *array_name)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%s[%d] = %s\n", array_name, i, array[i]);
		i++;
	}
	return (0);
}
