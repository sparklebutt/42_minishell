/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:43:28 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/10 15:45:51 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data)
{
	t_env	*env;
	int		found_key;

	env = data->env;
	found_key = find_node(env, "PATH", data); // make sure to check if every path value given in PATH is VALID
	
	// this is only needed if we don't want to handle [env -i ./minishell]
	// if (env == NULL) {
	// 	not_perror("env", NULL, "syntax error: WE DO NOT HANDLE env -i");
	// 	return ;
	// }
	
	if (found_key == 0 || found_key == 2) {
		not_perror("env", NULL, "No such file or directory\n");
		return ;
	}
	else
	{
		if (data->tokens->args[data->i + 1] != NULL && data->tokens->args[data->i + 1][0] != '|')
		{ 
			if (check_dir(data->tokens->args[data->i + 1]) == 0) {
				cmd_error("env", data->tokens->args[data->i + 1]);
				return ;
			}
		}
		while (env != NULL)
		{
			printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
	}
}
