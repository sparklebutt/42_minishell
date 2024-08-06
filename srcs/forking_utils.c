/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:01:07 by araveala          #+#    #+#             */
/*   Updated: 2024/08/05 18:02:46 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* function might already exist if not it could go with the node manipulation maybe */
static int	find_node_len(t_data *data)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = data->env;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
/*~~~ Here we set the null terminated array for exceve()'s second parameter,
this which contains the cmd, any flag and or argument that would go with the excecutable. ~~~*/

int	set_array(t_data *data)
{
	if (data->tmp->filename == NULL || data->tokens->args[data->i] == NULL)
	{
		// ft_printf("filename is NULL , we hve finsihed the pipes\n");
		return (-1);
	}
	if (data->tmp->filename != NULL)
	{
		data->tmp->ex_arr[0] = data->tmp->filename;
		data->i++;
	}
	if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] == '-')
	{
		data->tmp->ex_arr[1] = data->tokens->args[data->i];
		data->i++;
	}
	else
		data->tmp->ex_arr[1] = NULL;
	if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] != '|')
	{
		data->tmp->ex_arr[1] = data->tokens->args[data->i];
		// printf("checking arg = %s\n", data->tmp->ex_arr[1]);
		data->i++;
	}
	else
		data->tmp->ex_arr[2] = NULL; // arguments;
	data->tmp->ex_arr[3] = NULL; // last one is null
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
	i = find_node_len(data);
	data->env_array = malloc(i * sizeof(char *)); //must end in null
	if (data->env_array == NULL)
	{
		// perror maybe
		return ;
	}
	while (temp2 != NULL) // x <= i
	{
		key_full = ft_strjoin(temp2->key, "=");
		data->env_array[x] = ft_strjoin(key_full, temp2->value);
		free_string(key_full);
		x++;
		temp2 = temp2->next;
	}
	data->env_array[x - 1] = NULL; //ending in a null is a must
}

int	dup_fds(t_data *data, int *fds, int prev_fd, int x)
{
	if (x > 0) // not the first
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1) // read from prev	
		{
			printf("dup of prev failed\n");
			exit(1);
		}
	}
	if (x < data->tokens->pipe_count)
	{
		// ft_printf("hunting more 4 x = %d fd 0 = %d\n", x, fds[0]);			
		if (dup2(fds[1], STDOUT_FILENO) == -1) // write end
		{
			printf("dup of fds[1] failed\n");
			exit(1);
		}
	}
	close(fds[0]); // closing read end
	close(fds[1]);
	if (prev_fd != -1)
		close(prev_fd);
	return (0); // do we need to handle erros duiffewently
}
