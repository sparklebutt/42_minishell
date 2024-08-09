/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:56:54 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/09 10:34:59 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_unset(t_env *env, char *key_name)
{
	t_env *current = env, *prev = NULL;
	int len;

	len = ft_strlen(key_name);

	if (current != NULL && ft_strncmp(current->key, key_name, len) == 0)
	{
		env = current->next;
		free_string(current->key);
		free_string(current->value);
		free(current);
		return;
	}
	while (current != NULL && ft_strncmp(current->key, key_name, len) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return;
	prev->next = current->next;
	free_string(current->key);
	free_string(current->value);
	free(current);
}
