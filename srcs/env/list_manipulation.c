/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manipulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:47:46 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/12 14:31:05 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*move_list(t_env *envs, char *key)
{
	// do we need to combine all into data, we get very long lines ???
	t_env *temp;

	temp = envs;
	while (temp->next != NULL)// (1)
	{
		if (ft_strnstr(temp->key, key, ft_strlen(temp->key) + 1) && ft_strlen(temp->key) == ft_strlen(key))
			break ;
		temp = temp->next;
	}
	return (temp);
}

int find_node(t_env *envs, char *key, t_data *data)
{
	// do we need to combine all into data, we get very long lines ???
	t_env *temp;
	(void)data;
	
	if (!envs)
		return (0);
	temp = envs;
	while (temp->next != NULL)// (1)
	{
		// ft_printf("- - - - - - - - - - - - - - - - - - \n"); // remove
		// ft_printf("looking for key: %s|\n", key); // remove
		// ft_printf("temp->key: %s|\n", temp->key); // remove
		// ft_printf("temp->value: %s\n", temp->value); // places revious key as value???
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0 && (ft_strlen(temp->key) == ft_strlen(key)))
		{
			// ft_printf("key found\n"); // remove
			data->tmp->env_line = ft_strdup(temp->value);
			return (1);
		}
		temp = temp->next;
		if (temp->next == envs)
			break ;
	}
	free(key);
	// ft_printf("key not found\n");
	return (0);
}

void	remove_node(t_env *node)
{
	(void)node;
	// for unset 
}

void replace_value(t_data *data, char *key, char *new_value)
{
	t_env	*env;

	env = data->env;
	while (env->next != NULL)
	{
		env = env->next;
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
		{
			// ft_printf("key exists\n");
			free(env->value);
			env->value = new_value;
			free(key);
			return ;
		}
	}
}

char	*find_key(char *str)
{
	char *key;
	int i;

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

int	insert_node(t_env **env_lst, char *key_name, char *value)
{
	t_env	*new_node;
	t_env	*tmp;

	new_node = malloc(sizeof(t_env));
	if (new_node == NULL)
			return (-1);
	new_node->key = key_name;
	new_node->value = value;
	new_node->next = NULL;
	new_node->head = NULL;
	if (*env_lst == NULL)
	{
			*env_lst = new_node;
			return (1);
	}
	tmp = *env_lst;
	while (tmp->next != NULL)
			tmp = tmp->next;
	tmp->next = new_node;
	return (1);
}