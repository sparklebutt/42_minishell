/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:01:07 by araveala          #+#    #+#             */
/*   Updated: 2024/09/16 11:05:20 by araveala         ###   ########.fr       */
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
	return(arg_count);
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

static int	fill_output_info(t_data *data, int i)
{
	if (is_redirect(data->tokens->args[data->i]) != 2)
		data->tokens->action = true;	
	/* frankly i dont understand this anymore myself  */
	// neither do I, should we try making it make sense? 14.9
	// we could try using the is_redir function for these??

	// printf("\t\t\tdata->tokens->args[%d] = %s\n", data->i, data->tokens->args[data->i]);

	// if there isn't anything in input_file
	if (data->tokens->input_file != NULL) 
	{
		// if ex_arr[i - 1] == input_file, then move data->i
		if (ft_strncmp(data->tmp->ex_arr[i - 1],
			data->tokens->input_file, ft_strlen(data->tokens->input_file)) == 0)	
			data->i++;
		else
		{
			// else put the "output" (I'm assuming) into this ex_arr[i]
			// printf("\t\t\tdata->tokens->output_files[%d] = %s\n", data->x, data->tokens->output_files[data->x]);
			data->tmp->ex_arr[i] = data->tokens->output_files[data->x];
			data->i += 2;
		}
	}
	// new ---------------------------------------- 14.9
	else if (is_redirect(data->tokens->args[data->i]) == 2)
	{
		// printf("\t\t\tdata->tokens->here_file = %s\n", data->tokens->here_file);
		// data->tmp->ex_arr[i] = data->tokens->here_file; // replace with heredoc tempfile name!!
		data->i += 1;
	}
	else if (is_redirect(data->tokens->args[data->i]) == 3)  // added output redir aka > handling (not sure how or if it was handled before)
	{
		// printf("\t\t\tdata->tokens->output_files[%d] = %s\n", data->x, data->tokens->output_files[data->x]);
		data->tmp->ex_arr[i] = data->tokens->output_files[data->x];
		data->i += 2;
	}
	// --------------------------------------------
	else
	{
		// printf("\t\t\tSHOULD NOT GO HERE STUPID 3\n");
		data->tmp->ex_arr[i] = NULL;
		data->i++;
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
		else if (is_redirect(data->tokens->args[data->i]) >= 2) //carefull here it was != null
			fill_output_info(data, i);
		else
			data->tmp->ex_arr[i] = NULL;
	}
	else if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] != '|')
	{
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
		return (-1);
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
		if (i > 10)
			exit(1);
	}
	return (i);
}

/*~~~ here we tunr the envs into a null terminated array for the 3rd parameter of exceve(),
 taken from the env linked list as is up to dat must remeber to free all this data once we are done with it ~~~*/
char 	**set_env_array(t_data *data, int i, int x)
{
	t_env	*temp2;
	char **tmp_array;
	char	*key_full;
	
	tmp_array = NULL;
	temp2 = data->env;
	key_full = NULL;
	i = find_node_len(data);
	
	tmp_array = ft_calloc(i + 1, sizeof(char *));
	if (tmp_array == NULL)
		return (NULL);
	while (temp2 != NULL)
	{
		key_full = ft_strjoin(temp2->key, "=");
		tmp_array[x] = ft_strjoin(key_full, temp2->value);
		if (tmp_array[x] == NULL)
		{
			free_string(key_full);
			free_loop(tmp_array, x);
			break ;
		}
		free_string(key_full);
		x++;
		temp2 = temp2->next;
	}
	tmp_array[x] = NULL;	
	return (tmp_array);
}

int	dup_fds(t_data *data, int *fds, int x)
{
	if (data->tokens->array_count < 3)
		return (0);
	if (x > 0)
	{
		if (dup2(data->prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup of prev failed\n"); // change error message
			close(fds[0]);
			close(fds[1]);
			if (data->prev_fd != -1)
				close(data->prev_fd);
			exit(1); // exit code
		}
	}
	if (x < data->tokens->pipe_count)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
		{
			printf("dup of fds[1] failed\n"); // change error message
			close(fds[0]);
			close(fds[1]);
			if (data->prev_fd != -1)
				close(data->prev_fd);
			exit(1); //exit code
		}
	}
	close(fds[0]);
	close(fds[1]);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	return (0);
}