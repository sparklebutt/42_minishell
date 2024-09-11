/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:01:07 by araveala          #+#    #+#             */
/*   Updated: 2024/09/11 18:11:49 by araveala         ###   ########.fr       */
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
			i++;
		arg_count++;
		i++;
	}
	return(arg_count);
}

static int malloc_array(t_data *data, int i)
{
	if (data->tmp->ex_arr != NULL)
		free(data->tmp->ex_arr); // NEW FREE
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
	// cut this smaller
	if (data->tokens->args[data->i] != NULL && is_redirect(data->tokens->args[data->i]) > 0)
	{
		if (is_redirect(data->tokens->args[data->i]) == 1)
		{
			data->tmp->ex_arr[i] = data->tokens->input_file;
			data->i += 2;
		}
		else if (is_redirect(data->tokens->args[data->i]) == 3) //carefull lhere it was != null
		{
				printf("we found a redirect \n");
			//if (data->tokens->output_files[data->x] != NULL)
			data->tokens->action = true;	
			/* frankly i dont understand this anymore myself  */
			if (data->tokens->input_file != NULL) //what the fuck is this check?
			{
				data->tmp->ex_arr[i] = data->tokens->output_files[data->x];
				if (data->x < data->tokens->out_array_count)
					data->x++;
				data->i += 2;
			}
			else if (data->tokens->heredoc[0] != NULL)
			{
				//data->tokens->action = true;
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
		{
			//printf("at  %d else noo redir in redir nulled \n", i);
			//data->tokens->action = false;
			data->tmp->ex_arr[i] = NULL;
		}
	}
	else if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] != '|')
	{
		//printf("at  %d else noo redir take token \n", i);	
		//printf("at  %d truned action false \n", i);
		//data->tokens->action = false;
		data->tmp->ex_arr[i] = data->tokens->args[data->i];
		data->i++;
	}
	else
	{
		//printf("at  %d else noo anything nulled \n", i);	
		//printf("at  %d truned action false \n", i);
		//data->tokens->action = false;
		data->tmp->ex_arr[i] = NULL;
	}
	return (0);
}

int    set_array(t_data *data)
{
	int i;
	int arg_count;
	
	i  = 0;
	if (data->tmp->filename == NULL || data->tokens->args[data->i] == NULL)
	{
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
		//printf("what is going hre = %s\n", data->tokens->args[data->i]);
		fill_array(data, i);
		i++;
	}
	return (i); // potential line to get rid of
}

/*~~~ here we tunr the envs into a null terminated array for the 3rd parameter of exceve(),
 taken from the env linked list as is up to dat must remeber to free all this data once we are done with it ~~~*/
char 	**set_env_array(t_data *data, int i, int x)
{
	t_env	*temp2;
	char **tmp_array;
	char	*key_full;
	
	// cut this smaller
	tmp_array = NULL;
	temp2 = data->env;
	key_full = NULL;
	i = find_node_len(data);
	tmp_array = ft_calloc(i + 1, sizeof(char *)); // MALLOCED VARIABLE
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
	//dprintf(2, "pipe count = %d, x = %d\n", data->tokens->pipe_count , x);
	if (x > 0)// && x != data->tokens->pipe_count)
	{
		//dprintf(2, "dup in\n");
		if (dup2(data->prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup of prev failed\n");
			exit(1); //exit code
		}
	}
	if (x < data->tokens->pipe_count)
	{
		//dprintf(2, "dup out\n");	
		if (dup2(fds[1], STDOUT_FILENO) == -1)
		{
			printf("dup of fds[1] failed\n"); // change error message
			exit(1); //exit code
		}
	}
	close(fds[0]);
	close(fds[1]);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	return (0);
}
