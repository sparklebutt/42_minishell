/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:11:00 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/08 16:30:52 by vkettune         ###   ########.fr       */
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
	return (env);
}

t_env	*init(t_data *data)
{
	data->prompt = "\x1b[95mminishell\033[0;37m$ ";
	data->path = NULL;
	data->cmds = NULL;
	data->pid = 0;
	data->i = 0;
	return (create_env_list());
}
