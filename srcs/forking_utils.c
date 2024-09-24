/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:01:07 by araveala          #+#    #+#             */
/*   Updated: 2024/09/24 11:25:09 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_data *data)
{
	int	i;
	int	arg_count;

	arg_count = 0;
	i = data->i;
	while (data->tokens->args[i] != NULL && data->tokens->args[i][0] != '|')
	{
		if (is_redirect(data->tokens->args[data->i]) > 0)
			i++;
		else
		{
			arg_count++;
			i++;
		}
	}
	return (arg_count);
}

int	check_redirs(t_data *data)
{
	if (data->tokens->args[data->i] != NULL && is_redirect(data->tokens->args[data->i]) == 1)
	{
		data->tokens->input_file = free_string(data->tokens->input_file);
		data->tokens->input_file = ft_strdup(data->tokens->args[data->i + 1]);
		data->in_action = true;
		data->i += 2;
	}
	else if (is_redirect(data->tokens->args[data->i]) == 3)
	{
		data->tokens->action = true;
		data->i += 2;  
	}
	else if (is_redirect(data->tokens->args[data->i]) == 2)
	{
		data->h_action = true;
		data->i += 2;
	}
	return (0);
}

static int	malloc_array(t_data *data, int i)
{
	if (data->tmp->ex_arr != NULL)
	{
		free(data->tmp->ex_arr);
		data->tmp->ex_arr = NULL;
	}
	data->tmp->ex_arr = ft_calloc(i + 1, sizeof(char *));
	if (data->tmp->ex_arr == NULL)
	{
		printf("malloc fail handle here\n");
		return (1);
	}
	return (0);
}

static int    fill_array(t_data *data, int i)
{
	if (data->tokens->args[data->i] != NULL)
	{
		if (data->tokens->args[data->i] != NULL
			&& data->tokens->args[data->i][0] != '|' && is_redirect(data->tokens->args[data->i]) == 0)
		{
			data->tmp->ex_arr[i] = data->tokens->args[data->i];
			data->i++;
		}
		else if (data->tokens->args[data->i] != NULL && is_redirect(data->tokens->args[data->i]) > 0)
			return (1);
	}
	return (0);
}

int	set_array(t_data *data)
{
	int		i;
	int		arg_count;
	char	**args;

	i = 0;
	args = data->tokens->args;
	if (data->tmp->filename == NULL || args[data->i] == NULL)
		return (-1);
	arg_count = count_args(data);
	if (arg_count == 0)
		return (0);
	malloc_array(data, arg_count);
	if (data->tmp->filename != NULL)
	{
		data->tmp->ex_arr[0] = data->tmp->filename;
		i++;
		data->i++;
	}
	while (args[data->i] != NULL && args[data->i][0] != '|')
	{
		check_redirs(data);
		if (fill_array(data, i) == 0)
			i++;
	}
	return (i);
}
