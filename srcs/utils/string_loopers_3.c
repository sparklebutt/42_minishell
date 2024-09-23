/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_loopers_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:16:46 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/23 11:19:00 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redir_count(int token_count, int *count, int *comp_count)
{
	token_count++;
	(*comp_count) = (*count);
}

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

int	dup_fds(t_data *data, int *fds, int x)
{
	if (x > 0)
	{
		if (dup2(data->prev_fd, STDIN_FILENO) == -1)
		{
			perror("minishell: dup:\n");
			free_n_exit(data, fds, 2);
		}
	}
	if (x < data->tokens->pipe_count)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup: \n");
			free_n_exit(data, fds, 2);
		}
	}
	close(fds[0]);
	close(fds[1]);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	return (0);
}

void	simple_flagged(t_data *data, char *new, int len, int i)
{
	char	**exp_array;
	char	*tmp;
	int		flag;

	tmp = NULL;
	exp_array = data->tmp->exp_array;
	flag = check_next(exp_array[i + 1], ft_strlen(exp_array[i]));
	if (ft_strchr(exp_array[i], '"') != NULL
		|| ft_strchr(exp_array[i], '\'') != NULL)
	{
		new = clean_quotes(exp_array[i], len, 0, 0);
		tmp = look_if_expans(data, data->env, new, flag);
		exp_array[i] = free_string(exp_array[i]);
		exp_array[i] = ft_strdup((tmp));
		tmp = free_string(tmp);
	}
	else
		exp_array[i] = look_if_expans(data, data->env, exp_array[i], flag);
}

char	*set_the_string(t_data *data, char *line)
{
	char	*temp;
	char	*temp2;

	temp2 = NULL;
	temp = NULL;
	if (line != NULL && ft_strchr(line, '$') != NULL)
	{
		temp = look_if_expans(data, data->env, ft_strdup(line), 0);
		temp2 = ft_strjoin(temp, "\n");
		temp = free_string(temp);
		return (temp2);
	}
	else if (line != NULL)
		return (ft_strjoin(line, "\n"));
	return (NULL);
}
