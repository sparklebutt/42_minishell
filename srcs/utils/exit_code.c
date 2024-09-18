/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 08:40:21 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/19 00:35:38 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_code(int flag, int num)
{
	static int	error_code = 0;

	if (flag)
		error_code = num;
	return (error_code);
}

char	*replace_exitcode(char *arg, int start)
{
	char	*value;
	char	*new_arg;

	value = ft_itoa(exit_code(0, 0));
	new_arg = new_str(arg, value, start, start + 1 + 1);
	value = free_string(value);
	arg = free_string(arg);
	return (new_arg);
}

void	free_n_exit(t_data *data, int *fds, int flag)
{
	if (flag == 1)
		close(fds[1]);
	else if (flag == 2)
	{
		close(fds[0]);
		close(fds[1]);
		if (data->prev_fd != -1)
			close(data->prev_fd);
	}
	if (flag == 1 || flag == 0)
	{
		free_array(data->tokens->args);
		free_nodes(data->env);
		free_array(data->tokens->output_files);
	}
	exit(exit_code(0, 0));
}
