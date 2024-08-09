/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:11:33 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/09 10:38:14 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exit( char *cmd, t_tokens *tokens)
{
	// t_data *data,
	// t_env *envs;
	char *temp;

	temp = NULL;
	// envs = data->env;
	ft_printf("exit\n");
	if (tokens->args[1] != NULL && ft_strchr(tokens->args[1], '$') != 0)
	{
		// get $key from tokens->args[1]
		// and replace that value into tokens->args[1]
		if (temp == NULL)
		{
			temp = ft_strdup(tokens->args[1]);
			temp = ft_strchr(tokens->args[1], '$');
		}
	}
	// add into envs $?
	if (tokens->array_count > 1)
	{
		if (tokens->args[1] != NULL && atoi(tokens->args[1]) == 0)
			cmd_error(cmd, tokens->args[1]);
		else if (tokens->array_count > 2)
			cmd_error(cmd, NULL);
		free(cmd);
		exit(0);
	}
	free(cmd);
	exit(0);
	return (1);
}
