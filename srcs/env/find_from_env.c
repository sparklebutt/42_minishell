/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_from_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:02:41 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/09 17:04:43 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_keys_value(t_env *envs, char *key)
{
	t_env *temp;

	temp = envs;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
			return (temp->value);
		temp = temp->next;
	}
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
	return i;
}

int	find_node(t_env *envs, char *key, t_data *data)
{
	t_env	*temp;

	if (!envs)
		return (0);
	temp = envs;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0
			&& (ft_strlen(temp->key) == ft_strlen(key)))
		{
			free_string(data->tmp->env_line);
			data->tmp->env_line = ft_strdup(temp->value); // IF REMOVED THIS BREAKS "/bin/ls"
			return (1);
		}
		temp = temp->next;
		if (temp == NULL)
			break;
	}
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
		printf("error in finding key name\n"); // change error message
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
