/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_from_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:02:41 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/10 15:54:05 by vkettune         ###   ########.fr       */
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
	return (NULL);
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

int	find_node(t_env *envs, char *key, t_data *data)
{
	t_env	*temp;

	if (!envs)
		return (0);
	temp = envs;
	while (temp != NULL)
	{
		// printf("looking for = %s\n", key);
		// printf("key = %s\n", temp->key);
		// printf("value = %s\n", temp->value);
		// printf("------------------------\n");
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0
			&& (ft_strlen(temp->key) == ft_strlen(key)))
		{
			// printf("\t\tkey found!!!!\n");
			if (ft_strncmp("PATH", key, ft_strlen(key) + 1)	== 0 && find_keys_value(envs, "PATH") == NULL)
				return (2);
			data->tmp->env_line = temp->value;
			return (1);
		}
		temp = temp->next;
		// if (temp == NULL)
		// 	break;
	}
	// printf("\t\tkey NOT found!!!!\n");
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
	free_string(key);
	return (NULL);
}

char	*find_value(char *arg)
{
	char	*value;
	char	*temp;

	temp = ft_strchr(arg, '=');
	temp++;
	if (temp == NULL)
		return (NULL);
	value = ft_substr(temp, 1, ft_strlen(arg));
	if (value == NULL)
		return (NULL);
	return (value);
}
