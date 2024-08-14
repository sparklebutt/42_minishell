/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:11:00 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/12 11:53:32 by araveala         ###   ########.fr       */
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
	}
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
