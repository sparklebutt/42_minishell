/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:50:47 by vkettune          #+#    #+#             */
/*   Updated: 2025/07/09 16:00:20 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	initial_checks_and_setup(char **suffix, size_t *cmd_len,
		t_data *data, int x)
{
	char	**args;

	args = data->tokens->args;
	*cmd_len = ft_strlen(args[x]);
	if (*cmd_len == 0)
		return (0);
	if (args[x][0] == '.')
	{
		if (ft_strlen(args[x]) < 2)
			return (0);
		return (3);
	}
	if (args[x][0] == '/')
		return (handle_absolute_path(data, x, NULL), 3);
	if (args[x][0] != '/')
		*suffix = ft_strjoin("/", args[x]);
	if (*suffix == NULL)
		return (not_perror("check path", NULL, "malloc fail A\n"), 0);
	return (2);
}

int	match(t_temps *tmp, DIR *dir, char *suffix, int i)
{
	tmp->filename = ft_strjoin(tmp->array[i], suffix);
	suffix = free_string(suffix);
	closedir(dir);
	return (1);
}

int	iterate_and_match(char *suffix, size_t cmd_len, t_data *data, int x)
{
	DIR				*dir;
	struct dirent	*dp;
	int				i;

	i = 0;
	while (data->tmp->array && data->tmp->array[i])
	{
		if (check_dir(data->tmp->array[i]) == 1)
		{
			dir = opendir(data->tmp->array[i]);
			dp = readdir(dir);
			while (dp != NULL)
			{
				if (ft_strncmp(dp->d_name, data->tokens->args[x], cmd_len) == 0
					&& ft_strlen(dp->d_name) == cmd_len)
					return (match(data->tmp, dir, suffix, i));
				dp = readdir(dir);
			}
			closedir(dir);
		}
		i++;
	}
	suffix = free_string(suffix);
	return (0);
}

/* divert 1 = PATH, divert 2 = HOME*/
void	split_diversion(t_data *data, int divert, char *string)
{
	if (string == NULL || ft_strlen(string) == 0)
		return ;
	if (divert == 1)
		data->tmp->array = ft_split(string, ':');
	else if (divert == 2)
		data->tmp->array = ft_split(string, ' ');
	if (data->tmp->array == NULL)
		not_perror("check path", NULL, "malloc fail B\n");
}

int	check_path(char *string, int divert, t_data *data, int x)
{
	char	*suffix;
	size_t	cmd_len;
	int		res;

	cmd_len = 0;
	suffix = NULL;
	res = initial_checks_and_setup(&suffix, &cmd_len, data, x);
	if (res == 3)
	{
		if (check_file(data->tokens->args[x]) == 1)
			return (0);
		data->tmp->filename = ft_strdup(data->tokens->args[x]);
		return (res);
	}
	if (string == NULL)
		return (free_string_2(suffix, 0));
	if (res != 2)
		return (res);
	split_diversion(data, divert, string);
	res = iterate_and_match(suffix, cmd_len, data, x);
	free_array(data->tmp->array);
	if (res == 0)
		return (0);
	return (res);
}
