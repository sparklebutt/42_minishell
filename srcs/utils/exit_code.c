/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 08:40:21 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/21 08:58:39 by vkettune         ###   ########.fr       */
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


void free_stuff(t_data *data, int flag)
{
	if (flag == 0 || flag == 1)
	{
		free_array(data->tokens->args);
		free_array(data->tokens->output_files);
		data->tokens->output_files = NULL;
	}
	if (flag == 1)
		free_nodes(data->env);
}

void	free_n_exit(t_data *data, int *fds, int flag)
{
	if (flag == 1)
	{
		free(data->tmp->ex_arr);
		close(fds[1]);
	}
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
	if (data->tokens->here_file != NULL)
	{
		dprintf(2, "A UNLINK\n");
	 	unlink(data->tokens->here_file);
	 	data->tokens->here_file = free_string(data->tokens->here_file);
		free_array(data->tokens->heredoc);
		data->tokens->heredoc = NULL;
	}
	exit(exit_code(0, 0));
}
