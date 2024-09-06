/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:01:07 by araveala          #+#    #+#             */
/*   Updated: 2024/09/06 16:43:39 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_array(t_data *data)
{
	int i = 0; 
	
	if (data->tmp->filename == NULL || data->tokens->args[data->i] == NULL)
		return (-1);
	if (data->tmp->filename != NULL)
	{
		data->tmp->ex_arr[0] = data->tmp->filename;
		i++;
		data->i++;
	}
	// printf("is it redir? %d\n", is_redirect(data->tokens->args[data->i]));
	if (data->tokens->args[data->i] != NULL && is_redirect(data->tokens->args[data->i]) > 0)
	{
		if (is_redirect(data->tokens->args[data->i]) == 1)
		{
			data->tmp->ex_arr[1] = data->tokens->input_file;
			data->i += 2;
		}
		else if (is_redirect(data->tokens->args[data->i]) == 2) //carefull lhere it was != null
		{
		 	if (data->tokens->input_file != NULL)
			{	
				//printf("this shouod be putting it in now = %s\n", data->tokens->args[data->i]);
				//data->tmp->ex_arr[1] = data->tokens->args[data->i];
				data->tmp->ex_arr[1] = data->tokens->output_files[data->x];
				data->i += 2;
			}
			else if (data->tokens->heredoc[0] != NULL)
			{
				data->tmp->ex_arr[1] = data->tokens->heredoc[0]; // replace with heredoc tempfile name!!
				data->i += 2;
			}
			else
			{
				data->tmp->ex_arr[1] = NULL;		
				data->i++;
			}
		}
		else
			data->tmp->ex_arr[1] = NULL;
	}
	//else if (data->tokens->args[data->i][0] == '|')
	//	dprintf(2, "the fuck\n");
	else if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] != '|' && data->tokens->args[data->i][0]) // && is_redirect(data->tokens->args[data->i]) == 0)
	{
		// printf("did it do the thing = %s\n", data->tokens->args[data->i]);
		data->tmp->ex_arr[1] = data->tokens->args[data->i];
		i++;
		data->i++;
	}
	else
	{
		data->tmp->ex_arr[1] = NULL;
	}
	///just as example this is where the loop maybe should start again??
	/*if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] != '|')
	{
		data->tmp->ex_arr[2] = data->tokens->args[data->i]; // arguments;
		data->i++;
	}
	else*/
	data->tmp->ex_arr[2] = NULL; // arguments;
	data->tmp->ex_arr[3] = NULL; // last one is null
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
	i = find_node_len(data) + 1;
	data->env_array = ft_calloc(i, sizeof(char *)); // was malloc
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
