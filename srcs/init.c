/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:11:00 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/09 20:42:00 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_list(t_data *data)
{
	extern char **environ;
	int i;
	char *value;
	char *key;
	t_env *temp_env;
	t_env *env;

	(void)data;
	i = 0;
	env = NULL;
	temp_env = env;
	if (environ[i] == NULL)
	{
		insert_node(&env, "SHLVL", "1"); // change this to update number, add other default nodes into env, check "env -i ./minishell" and "env -i bash"
			return (env) ;
	}
	while (environ[i] != NULL)
	{
		value = find_value(environ[i]);
		key = find_key(environ[i]);
		insert_node(&env, key, value);
		i++;
		if (ft_strncmp(key, "PWD", 4) == 0)
			insert_node(&env, ft_strdup("OLDPWD"), ft_strdup(value));
		if (ft_strncmp(key, "PWD", 4) == 0)
			i++;
	}
	
	// this breaks env, but we need it somehow like this in here. OLDPWD is in env twice!!!!!
	//
	// if (find_keys_value(env, "OLDPWD") != 0)
	// {
	// 	value = find_keys_value(env, "PWD");
	// 	printf("value = %s\n", value);
	// 	if (value == NULL)
	// 		return NULL;
	// 	temp_env = replace_value(env, ft_strdup("OLDPWD"), ft_strdup(value));
	// 	return (temp_env);
	// }
	// else if (find_node(env, "PWD", data) == 0)
	// 	insert_node(&env, ft_strdup("OLDPWD"), ft_strdup(value));
	return (env);
}

t_env	*init(t_data *data)
{
	data->prompt = "\x1b[95mminishell\033[0;37m$ ";
	data->path = NULL;
	data->cmds = NULL;
	data->pid = 0;
	data->i = 0;
	return (create_env_list(data));
}
