/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:01:07 by araveala          #+#    #+#             */
/*   Updated: 2024/09/19 11:32:15 by vkettune         ###   ########.fr       */
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
		arg_count++;
		i++;
	}
	return (arg_count);
}

static int	malloc_array(t_data *data, int i)
{
	if (data->tmp->ex_arr != NULL)
		free(data->tmp->ex_arr);
	data->tmp->ex_arr = ft_calloc(i + 1, sizeof(char *));
	if (data->tmp->ex_arr == NULL)
	{
		printf("malloc fail handle here\n");
		return (1);
	}
	return (0);
}

/* frankly i dont understand this anymore myself 
neither do I, should we try making it make sense? 14.9
we could try using the is_redir function for these??
if there isn't anything in input_file*/
static int	fill_output_info(t_data *data, int i)
{
	if (is_redirect(data->tokens->args[data->i]) != 2)
		data->tokens->action = true;
	if (data->tokens->input_file != NULL)
	{
		if (ft_strncmp(data->tmp->ex_arr[i - 1], data->tokens->input_file,
				ft_strlen(data->tokens->input_file)) == 0)
			data->i++;
		else
		{
			data->tmp->ex_arr[i] = data->tokens->output_files[data->x];
			data->i += 2;
		}
	}
	else if (is_redirect(data->tokens->args[data->i]) == 2)
		data->i += 2;
	else
	{
		data->tmp->ex_arr[i] = NULL;
		data->i++;
	}
	return (0);
}

static int	fill_array(t_data *data, int i)
{
	if (data->tokens->args[data->i] != NULL
		&& is_redirect(data->tokens->args[data->i]) > 0)
	{
		if (is_redirect(data->tokens->args[data->i]) == 1)
		{
			data->tmp->ex_arr[i] = data->tokens->input_file;
			data->i += 2;
		}
		else if (is_redirect(data->tokens->args[data->i]) >= 2)
			fill_output_info(data, i);
		else
			data->tmp->ex_arr[i] = NULL;
	}
	else if (data->tokens->args[data->i] != NULL
		&& data->tokens->args[data->i][0] != '|')
	{
		data->tmp->ex_arr[i] = data->tokens->args[data->i];
		data->i++;
	}
	else
		data->tmp->ex_arr[i] = NULL;
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
	{
		// printf("set array is -1\n");
		return (-1);
	}
	arg_count = count_args(data);
	malloc_array(data, arg_count);
	if (data->tmp->filename != NULL)
	{
		data->tmp->ex_arr[0] = data->tmp->filename;
		i++;
		data->i++;
	}
	while (args[data->i] != NULL && args[data->i][0] != '|')
	{
		fill_array(data, i);
		i++;
	}
	return (i);
}
