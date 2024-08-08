/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_from_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:02:41 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/08 16:23:32 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_keys_value(t_env *envs, char *key)
{
	t_env *temp;

	temp = envs;
	while (temp != NULL)
	{
		// ft_printf("key: %s\n", temp->key); // remove
		// ft_printf("value: %s\n", temp->value); // remove
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
			return (temp->value);
		temp = temp->next;
	}
	// printf("error!!!! null\n");
	return (0);
}

int	find_node_len(t_data *data)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = data->env;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
