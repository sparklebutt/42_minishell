/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_loopers_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:16:46 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/20 18:17:35 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_env_arr_loop(t_env	*temp2, char **tmp_array, int x,
	char *key_full)
{
	while (temp2 != NULL)
	{
		key_full = ft_strjoin(temp2->key, "=");
		tmp_array[x] = ft_strjoin(key_full, temp2->value);
		if (tmp_array[x] == NULL)
		{
			key_full = free_string(key_full);
			free_loop(tmp_array, x);
			break ;
		}
		key_full = free_string(key_full);
		x++;
		temp2 = temp2->next;
	}
	tmp_array[x] = NULL;
	return (tmp_array);
}

/*~~~ here we tunr the envs into a null terminated array
for the 3rd parameter of exceve(), taken from the env linked list
as is up to dat must remeber to free all this data once we are
done with it ~~~*/
char	**set_env_array(t_data *data, int i, int x)
{
	t_env	*temp2;
	char	**tmp_array;
	char	*key_full;

	tmp_array = NULL;
	temp2 = data->env;
	key_full = NULL;
	i = find_node_len(data);
	tmp_array = ft_calloc(i + 1, sizeof(char *));
	if (tmp_array == NULL)
		return (NULL);
	return (fill_env_arr_loop(temp2, tmp_array, x, key_full));
}

// change error messages to perror, and change error func's
int	dup_fds(t_data *data, int *fds, int x)
{
	if (x > 0)
	{
		if (dup2(data->prev_fd, STDIN_FILENO) == -1)
		{
			free_n_exit(data, fds, 2);
			perror("dup of prev failed\n");
		}
	}
	if (x < data->tokens->pipe_count)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
		{
			free_n_exit(data, fds, 2);
			printf("dup of fds[1] failed\n");
		}
	}
	close(fds[0]);
	close(fds[1]);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	return (0);
}