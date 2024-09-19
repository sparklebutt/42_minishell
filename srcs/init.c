/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:11:00 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/19 07:00:18 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// change SHLVL to update the number, add other default nodes into env,
// check "env -i ./minishell" and "env -i bash"
t_env	*create_env_list(char *value, char *key, char *temp)
{
	extern char	**environ;
	int			i;
	t_env		*env;

	i = 0;
	env = NULL;
	if (environ[i] == NULL)
	{
		temp = getcwd(NULL, 0);
		insert_node(&env, ft_strdup("PWD"), temp);
		insert_node(&env, ft_strdup("SHLVL"), ft_strdup("1"));
		insert_node(&env, ft_strdup("_"), ft_strdup("/usr/bin/env"));
		return (env);
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
	//data->cmds = NULL;
	//data->pid = 0;
	data->i = 0;
	//data->builtin_marker = false;
	return (create_env_list(NULL, NULL, NULL));
}
