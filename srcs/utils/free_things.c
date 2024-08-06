/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:59:15 by araveala          #+#    #+#             */
/*   Updated: 2024/07/12 16:07:54 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_extra_return_function(char *str, int ret_value)
{
	free_string(str);
	return (ret_value);
}

void	free_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	if (array != NULL)
	{
		free(array);
		array = NULL;
	}
}

void	free_array_2(char **array, int x)
{
	int i;

	i = 0;
	while (i < x)
	{
		if (array[i] != NULL)
			free(array[i]);
		array[i] = NULL;
		i++;
	}
	if (array != NULL)
	{
		free(array);
		array = NULL;
	}
}

void	free_string(char *string)
{
	if (string != NULL)
	{
		free(string);
		string = NULL;
	}
	else
		string = NULL;
}

void	free_nodes(t_env *node)
{
	t_env *tmp;
	while (node != NULL)
	{
		if (node->value)
			free(node->value);
		free(node->key);
		tmp = node;
		node = node->next;
		free(tmp);
	}
}

int error(char *cmd, char *error)
{
	ft_printf("minishell: %s: %s\n", cmd, error); //perror
	return (1);
}

void	collective_free(char *str1, char *str2, char **array)
{
//	if (array != NULL)
	free_array(array);
	array = NULL;	
//	if (str1 != NULL)
	free_string(str1);
	str1 = NULL;
//	if (str2 != NULL)
	free_string(str2);
	str2 = NULL;

}
