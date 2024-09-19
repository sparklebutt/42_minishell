/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:11:33 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/19 10:12:42 by vkettune         ###   ########.fr       */
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
	free_n_exit(data, 0, 0);
}
