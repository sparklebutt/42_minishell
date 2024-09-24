/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_loopers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:08:22 by araveala          #+#    #+#             */
/*   Updated: 2024/09/24 15:58:36 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_echo_loop(char **args, int *x, int *i)
{
	char	*temp;

	(*x) = ft_strlen(args[*i]) + 2;
	temp = ft_calloc(*x, sizeof(char));
	if (temp == NULL)
		return (not_perror("echo", NULL, "malloc fail\n"), -1);
	temp[0] = 0x06;
	ft_strcpy(temp + 1, args[*i]);
	free_string(args[*i]);
	args[*i] = ft_strdup(temp);
	free_string(temp);
	(*i)++;
	(*x) = 0;
	return (0);
}

int	parse_redir_loop(t_data *data, int *i, int *x)
{
	char	**args;
	int		fd;

	fd = 0;
	args = data->tokens->args;
	if (ft_strlen(args[*i]) == 2 && ft_strncmp(args[*i], "<<", 2) == 0)
		heredoc_loop(data, 0, data->tokens, args[*i + 1]);
	else if (args[*i + 1] != NULL && is_redirect(args[*i]) == 1)
		input_helper(data->tokens, fd, *i);
	else if (args[*i + 1] != NULL && (ft_strncmp(args[*i], ">>", 2) == 0
			|| ft_strncmp(args[*i], ">", 1) == 0))
		output_helper(data->tokens, fd, *i, *x);
	return (0);
}

int	redir_collect_loop(char **array, int i, int *count)
{
	if (ft_strlen(array[i]) > 2)
	{
		if (array[i][2])
			return (not_perror("syntax error", NULL, "too many redirects\n"), -1);
	}
	(*count)++;
	return (0);
}

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

