/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_from_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:02:41 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/12 12:03:34 by araveala         ###   ########.fr       */
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
		//printf("what is temp key = %s and our i = %d\n", temp->key, i);
		temp = temp->next;
		i++;
	}
	return (i - 1);
}

int	find_node(t_env *envs, char *key, t_data *data)
{
	t_env	*temp;
	(void)data;

	if (!envs)
		return (0);
	temp = envs;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0
			&& (ft_strlen(temp->key) == ft_strlen(key)))
		{
			// ft_printf("key found\n"); // remove
			data->tmp->env_line = ft_strdup(temp->value); // IF REMOVED THIS BREAKS "/bin/ls"
			return (1);
		}
		temp = temp->next;
		if (temp == NULL)
			break;
	}
	// ft_printf("key not found\n");
	return (0);
}

char	*find_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	key = NULL;
	while (str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		key = ft_substr(str, 0, i);
		return (key);
	}
	else
		printf("error in finding key name\n");
	free(key);
	return (NULL);
}

char	*find_value(char *arg)
{
	char	*value;
	char	*temp;

	temp = ft_strchr(arg, '=');
	if (temp == NULL)
		return (NULL);
	value = ft_substr(temp, 1, ft_strlen(arg));
	if (value == NULL)
		return (NULL);
	return (value);
}
