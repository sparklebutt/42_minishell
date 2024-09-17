/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_from_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:02:41 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/17 15:33:03 by vkettune         ###   ########.fr       */
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
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0
			&& (ft_strlen(temp->key) == ft_strlen(key)))
		{
			// printf("\t\tkey found!!!!\n");
			if (ft_strncmp("PATH", key, ft_strlen(key) + 1)	== 0 && find_keys_value(envs, "PATH") == NULL)
				return (2);
			// printf("not in find value\n");
			data->tmp->env_line = temp->value;
			return (1);
		}
		temp = temp->next;
		//if (temp == NULL)
		 //	break;
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
		if (key == NULL)
			return (NULL);
		return (key);
	}
	else
		printf("error in finding key name\n"); // change error message
	return (NULL);
}

char	*find_value(char *arg)
{
	char	*value;
	char	*temp;

	temp = ft_strchr(arg, '=');
	value = NULL;
	/*CHANGE temp++*/
	//temp++; // this was causing us to loose a character in key value
	if (temp == NULL)
		return (NULL);
	value = ft_substr(temp, 1, ft_strlen(arg));
	if (value == NULL)
		return (NULL);
	//arg = free_string(arg);
	return (value);
}
