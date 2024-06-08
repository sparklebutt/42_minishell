/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:56:15 by araveala          #+#    #+#             */
/*   Updated: 2024/06/08 16:16:44 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_key_name(char *string)
{
	char *name;
	int i;

	i = 0;
	name = NULL;
	while (string[i])
	{
		
		if (string[i] == '=')
		{
			name = ft_substr(string, 0, i);
			return (name);
		}
		i++;
	}
	printf("error in finding key name\n");
	return (0);
}

t_env	*lst_env(void)
{
	extern char **environ;
	int i;
	char *value;
	char *key_name;
	t_env *envs;

	i = 0;
	envs = NULL;
	while (environ[i] != NULL)
	{
		value = find_value(environ[i]);
		key_name = find_key_name(environ[i]);
		insert_node(&envs, key_name, value);
		// test = add_new_node(environ[i], key_name);
		// addnode(&envs, test);//add_new_node(environ[i], key_name));
		i++;
	// }
		// while (i-- > 0 && envs->next != NULL)
		// {
		// 	envs = envs->next;
		// 	ft_printf("- - - - - - - - - - - - - - - - - - \n");
		// 	ft_printf("A envs->key: %s\n", envs->key);
		// 	ft_printf("A envs->value: %s\n", envs->value);
		// 	ft_printf("- - - - - - - - - - - - - - - - - - \n");
		// 	envs = envs->prev;
		// 	ft_printf("B envs->key: %s\n", envs->key);
		// 	ft_printf("B envs->value: %s\n", envs->value);
		// 	ft_printf("- - - - - - - - - - - - - - - - - - \n");
		// }
	}
	return (envs);
}

char *find_key_from_envs(t_env *envs, char *key)
{
	t_env *temp;

	temp = envs;
	ft_printf("key: %s\n", key);
	while (temp->next != NULL)
	{
		ft_printf("key: %s\n", temp->key); // remove
		ft_printf("value: %s\n", temp->value); // remove
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (0);
}
