/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:11:00 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/12 14:30:36 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_list(void)
{
	extern char **environ;
	int i;
	char *value;
	char *key;
	t_env *env;

	i = 0;
	env = NULL;
	if (environ[i] == NULL)
	{
		insert_node(&env, "SHLVL", "1");
				return (env) ;
	}
	while (environ[i] != NULL)
	{
		value = find_value(environ[i]);
		key = find_key(environ[i]);
		insert_node(&env, key, value);
		// fill head into each node or have it in data?
		i++;
		if (ft_strncmp(key, "PWD", 4) == 0)
			insert_node(&env, ft_strdup("OLDPWD"), ft_strdup(value));
		if (ft_strncmp(key, "PWD", 4) == 0)
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
	return (create_env_list());
}
