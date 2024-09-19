/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:50:47 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/19 14:20:19 by vkettune         ###   ########.fr       */
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

// if this leaks, add these back and figure out how to cut this func
// dir = NULL;
// dp = NULL;
int	iterate_and_match(char *suffix, size_t cmd_len, t_data *data, int x)
{
	DIR				*dir;
	struct dirent	*dp;
	int				i;

	i = 0;
	while (data->tmp->array[i])
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
				if (i != 0)
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
void	split_diversion(t_temps *tmp, int divert, char *string)
{
	if (divert == 1)
		tmp->array = ft_split(string, ':');
	else if (divert == 2)
		tmp->array = ft_split(string, ' ');
	if (tmp->array == NULL)
		not_perror("check path", NULL, "malloc fail B\n");
}

/* checking access and creating sub tokens for easy access 
in children res = 3 means we are looking into current directory
so we do not need to check_dir but file muts be checked, this is
 eg so that minishell can run inside minishell*/
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
	if (res != 2)
		return (res);
	split_diversion(data->tmp, divert, string);
	res = iterate_and_match(suffix, cmd_len, data, x);
	free_array(data->tmp->array);
	if (res == 0)
		return (0);
	return (res);
}
