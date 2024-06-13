/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:43:28 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/13 09:12:25 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data) // is needs work
{
	t_env	*env;
	t_env	*temp;
	char	*key;
	char	*value;

	env = data->env;
	key = find_key("PATH");
	value = 0;
	if (key == 0)
	{
		cmd_error("env", NULL, "No such file or directory");
		return ;
	}
	else // how do we check that PATH is valid?
	{
		value = find_keys_value(env, key);
		if (value != 0)
		{
			temp = move_list(env, key);
			if (temp->value != NULL) // or invalid
				ft_printf("PATH=%s\n", temp->value);
			// do smth with temp->value here
			// free(value);
		}
		free(key);
	}
	if (data->tokens->args[1] != NULL) // gives error with "env dfgh"
	{
		cmd_error("env", data->tokens->args[1], "No such file or directory");
		return ;
	}
	// move env to the start of the list, prints env starting PATH
	while (env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	// fix segfault with "env -i ./minishell"
}
