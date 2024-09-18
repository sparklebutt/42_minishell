/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:11:33 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/18 08:09:03 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data, char *cmd, t_tokens *tokens)
{
	char	*temp;

	(void)data;
	temp = NULL;
	ft_printf("exit\n");
	if (tokens->args[1] != NULL && ft_strchr(tokens->args[1], '$') != 0)
	{
		if (temp == NULL)
		{
			temp = ft_strdup(tokens->args[1]);
			temp = ft_strchr(tokens->args[1], '$');
		}
	}
	if (tokens->array_count > 1)
	{
		if (tokens->args[1] != NULL && ft_atoi(tokens->args[1]) == 0)
			cmd_error(cmd, tokens->args[1]);
		else if (tokens->array_count > 2)
			cmd_error(cmd, NULL);
	}
	// cmd = free_string(cmd); // maybe needed
	free_array(tokens->args);
	free_nodes(data->env);
	free_array(tokens->output_files);
	exit(exit_code(0, 0));
}
