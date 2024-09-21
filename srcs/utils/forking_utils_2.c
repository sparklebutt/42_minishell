/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:25:28 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/21 13:29:06 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_bools(t_data *data, char *args)
{
	if (is_redirect(args) == 3)
		data->tokens->action = true;
	else if (is_redirect(args) == 2)
		data->tokens->h_action = true;
	else if (is_redirect(args) == 1)
		data->in_action = true;
}

void	execve_fail(t_data *data, char **tmp, int *fds)
{
	tmp = set_env_array(data, 0, 0);
	reset_signals(0);
	if (data->tmp->filename != NULL)
		execve(data->tmp->filename, data->tmp->ex_arr, tmp);
	free_array(tmp);
	free_n_exit(data, fds, 1);
}

void	after_child(t_data *data, int *fds)
{
	data->tokens->h_action = false;
	data->tokens->action = false;
	data->in_action = false;
	data->child_i++;
	if (data->prev_fd != -1)
		close(data->prev_fd);
	close(fds[1]);
	data->tmp->filename = free_string(data->tmp->filename);
}

int	set_builtin_info(t_data *data, int fds[2], int x)
{
	int	i;

	i = data->i;
	while (data->tokens->args[i] != NULL && data->tokens->args[i][0] != '|')
	{
		if (is_redirect(data->tokens->args[i]) > 0)
		{
			data->tokens->action = true;
			break ;
		}
		i++;
	}
	child(data, fds, x, 1);
	data->i++;
	while (data->tokens->args[data->i] != NULL)
	{
		if (data->tokens->args[data->i][0] == '|')
		{
			data->i++;
			break ;
		}
		data->i++;
	}
	return (0);
}

int	send_to_child_help(t_data *data, int fds[2], int x)
{
	char	**args;

	args = data->tokens->args;
	set_array(data);
	child(data, fds, x, 0);
	if (data->i == data->tokens->array_count)
		return (1);
	if (args[data->i] != NULL && args[data->i][0] == '|')
		data->i++;
	return (0);
}
