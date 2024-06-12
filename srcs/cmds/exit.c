/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:11:33 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/11 08:41:44 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exit(t_data *data, char *cmd, t_tokens *tokens) // this should now be pretty good
{
	t_env *envs;
	char *temp;

	temp = NULL;
	envs = data->env;
	ft_printf("exit\n");
	if (ft_strchr(tokens->args[1], '$') != 0)
	{
		// get $key from tokens->args[1]
		// and replace that value into tokens->args[1]
		temp = ft_strdup(tokens->args[1]);
		temp = ft_strchr(tokens->args[1], '$');
		
	}
	// add into envs $?
	if (tokens->array_count > 1)
	{
		if (atoi(tokens->args[1]) == 0)
			cmd_error(cmd, tokens->args[1], "numeric argument required\n");
		else if (tokens->array_count > 2)
			cmd_error(cmd, NULL, "too many arguments\n");
		
		free(cmd);
		exit(0);
	}
	free(cmd);
	exit(0);
	return (1);
}
