/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:11:33 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/21 12:50:13 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data, char *cmd, t_tokens *tokens)
{
	char	*temp;

	temp = NULL;
	ft_printf("exit\n");
	if (tokens->array_count > 1)
	{
		if (tokens->array_count > 2)
			return (not_perror(cmd, NULL, "too many arguments\n"));
		else if (tokens->args[1] != NULL && ft_atoi(tokens->args[1]) == 0)
			not_perror(cmd, tokens->args[1], "numeric argument required\n");
	}
	free_n_exit(data, 0, 0);
}
