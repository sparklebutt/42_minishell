/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:43:28 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/05 15:08:19 by araveala         ###   ########.fr       */
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
		cmd_error("env", NULL);
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
	/* ~~ below error handeling is porblematic with pipes
	   ive written an alternative below it that works with pipes ~~*/
	/*if (data->tokens->args[1] != NULL) // gives error with "env dfgh"
	{
		cmd_error("env", data->tokens->args[1]);
		return ;
	}*/
	if (data->tokens->args[data->i + 1][0] != '|' && data->tokens->args[data->i + 1] != NULL)
	{
		if (check_dir(data->tokens->args[data->i + 1]) == 0)
		{
			cmd_error("env", data->tokens->args[data->i + 1]);
			return ;
		}
	}
	// move env to the start of the list, prints env starting PATH
	while (env != NULL)
	{
		// write(2, "printing env\n", 13);
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	// fix segfault with "env -i ./minishell"
}
