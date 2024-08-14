/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:01:07 by araveala          #+#    #+#             */
/*   Updated: 2024/08/13 16:34:47 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*~~~ Here we set the null terminated array for exceve()'s second parameter,
this which contains the cmd, any flag and or argument that would go with the excecutable. ~~~*/

int	set_array(t_data *data)
{
	if (data->tmp->filename == NULL || data->tokens->args[data->i] == NULL)
		return (-1);
	if (data->tmp->filename != NULL)
	{
		data->tmp->ex_arr[0] = data->tmp->filename;
		data->i++;
	}
	if (data->tokens->args[data->i] != NULL
		&& data->tokens->args[data->i][0] == '-')
	{
		data->tmp->ex_arr[1] = data->tokens->args[data->i];
		data->i++;
	}
	else
		data->tmp->ex_arr[1] = NULL;
	// if (data->tokens->args[data->i] )
	if (data->tokens->args[data->i] != NULL
		&& data->tokens->args[data->i][0] != '|') //&& 
	{
		// printf("HHHHHH args: %s\n", data->tokens->args[data->i]);
		// printf("set array args[data->i] = %s\n", data->tokens->args[data->i]);
		if (is_redirect(data->tokens->args[data->i]) == 1)
			data->tmp->ex_arr[1] = data->tokens->input_file;
		else if (is_redirect(data->tokens->args[data->i]) == 2)
			data->tmp->ex_arr[1] = data->tokens->output_file;
		else
			data->tmp->ex_arr[1] = data->tokens->args[data->i];
		data->i++;
	}
	else
		data->tmp->ex_arr[2] = NULL; // arguments;
	data->tmp->ex_arr[3] = NULL; // last one is null
	//printf();
	return (data->i); // potential line to get rid of
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
	i = find_node_len(data) + 1;
	data->env_array = malloc(i * sizeof(char *)); // changed to add 1
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
	data->env_array[x - 1] = NULL;
}

int	dup_fds(t_data *data, int *fds, int prev_fd, int x)
{
	write(2, "duping\n", 7);
	if (x > 0)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			printf("dup of prev failed\n"); // change error message
			exit(1);
		}
	}
	if (x < data->tokens->pipe_count)
	{
		write(2, "dup out\n", 7);
		if (dup2(fds[1], STDOUT_FILENO) == -1)
		{
			printf("dup of fds[1] failed\n"); // change error message
			exit(1);
		}
	}
	close(fds[0]);
	close(fds[1]);
	if (prev_fd != -1)
		close(prev_fd);
	return (0);
}
