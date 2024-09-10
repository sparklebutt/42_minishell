/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:01:07 by araveala          #+#    #+#             */
/*   Updated: 2024/09/10 12:14:17 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_args(t_data *data)
{
	int i;
	int arg_count;

	arg_count = 0;
	i = data->i;
	while (data->tokens->args[i] != NULL && data->tokens->args[i][0] != '|')
	{
		if (is_redirect(data->tokens->args[data->i]) > 0)
		{
			i++;
		}
		arg_count++;
		i++;    
	}
	return(arg_count);
}

static int malloc_array(t_data *data, int i)
{
	// free_array(data->tmp->ex_arr); // nope
	data->tmp->ex_arr = ft_calloc(i + 1, sizeof(char *)); // MALLOCED VARIABLE
	if (data->tmp->ex_arr == NULL)
	{
		printf("malloc fail handle here\n");
		return (1);
	}
	return (0); 
}

static int fill_array(t_data *data, int i)
{
	if (data->tokens->args[data->i] != NULL && is_redirect(data->tokens->args[data->i]) > 0)
	{
		if (is_redirect(data->tokens->args[data->i]) == 1)
		{
			data->tmp->ex_arr[i] = data->tokens->input_file;
			data->i += 2;
		}
		else if (is_redirect(data->tokens->args[data->i]) == 2) //carefull lhere it was != null
		{
			if (data->tokens->input_file != NULL)
			{
				data->tmp->ex_arr[i] = data->tokens->output_files[data->x];
				data->i += 2;
			}
			else if (data->tokens->heredoc[0] != NULL)
			{
				data->tmp->ex_arr[i] = data->tokens->heredoc[0]; // replace with heredoc tempfile name!!
				data->i += 2;
			}
			else
			{
				data->tmp->ex_arr[i] = NULL;        
				data->i++;
			}
		}
		else
			data->tmp->ex_arr[i] = NULL;
	}
	else if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] != '|')
	{
		// printf("sticking this = %s |||into ex_arr", data->tokens->args[data->i]);
		data->tmp->ex_arr[i] = data->tokens->args[data->i];
		data->i++;
	}
	else
		data->tmp->ex_arr[i] = NULL;
	return (0);
}

int    set_array(t_data *data)
{
	int i;
	int arg_count;
	
	i  = 0;
	if (data->tmp->filename == NULL || data->tokens->args[data->i] == NULL)
	{
		printf("filename = NULL\n");
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
	while (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] != '|')
	{
		fill_array(data, i);
		i++;
	}
	return (i); // potential line to get rid of
}

/*~~~ here we tunr the envs into a null terminated array for the 3rd parameter of exceve(),
 taken from the env linked list as is up to dat must remeber to free all this data once we are done with it ~~~*/
void	set_env_array(t_data *data)
{
	int		i;
	int		x;
	t_env	*temp2;
	char	*key_full;

	x = 0;
	temp2 = data->env;
	key_full = NULL;
	i = find_node_len(data);
	free_array(data->env_array);
	data->env_array = ft_calloc(i + 1, sizeof(char *)); // MALLOCED VARIABLE
	if (data->env_array == NULL)
		return ;
	while (temp2 != NULL)
	{
		key_full = ft_strjoin(temp2->key, "=");
		data->env_array[x] = ft_strjoin(key_full, temp2->value);
		free_string(key_full);
		x++;
		temp2 = temp2->next;
	}
	// printf("x = %d and i = %d\n", x, i);
	data->env_array[i] = NULL;
}

int	dup_fds(t_data *data, int *fds, int x)
{
	if (x > 0)
	{
		if (dup2(data->prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup of prev failed\n");
			exit(1);
		}
	}
	if (x < data->tokens->pipe_count)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
		{
			printf("dup of fds[1] failed\n"); // change error message
			exit(1);
		}
	}
	close(fds[0]);
	close(fds[1]);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	return (0);
}
