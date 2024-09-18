/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:50:47 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/18 11:52:35 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	initial_checks_and_setup(char **suffix, size_t *cmd_len, t_data *all, int x)
{
	*cmd_len = ft_strlen(all->tokens->args[x]);
	if (*cmd_len == 0)
		return (0);
	if (all->tokens->args[x][0] == '.')
		return (3);
	if (all->tokens->args[x][0] == '/')
		return (handle_absolute_path(all, x, NULL), 3);
	if (all->tokens->args[x][0] != '/')
		*suffix = ft_strjoin("/", all->tokens->args[x]);
	if (*suffix == NULL)
		return (not_perror("check path", NULL, "malloc fail A"), 0);
	return (2);
}

int	match(t_data *all, DIR *dir, char *suffix, int i)
{
	all->tmp->filename = ft_strjoin(all->tmp->array[i], suffix);
	suffix = free_string(suffix);
	closedir(dir);
	return (1);
}

// if this leaks, add these back and figure out how to cut this func
// dir = NULL;
// dp = NULL;
int	iterate_and_match(char *suffix, size_t cmd_len, t_data *all, int x)
{
	DIR				*dir;
	struct dirent	*dp;
	int				i;

	i = 0;
	while (all->tmp->array[i])
	{
		if (check_dir(all->tmp->array[i]) == 1)
		{
			dir = opendir(all->tmp->array[i]);
			dp = readdir(dir);
			while (dp != NULL)
			{
				if (ft_strncmp(dp->d_name, all->tokens->args[x], cmd_len) == 0
					&& ft_strlen(dp->d_name) == cmd_len)
					return (match(all, dir, suffix, i));
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
void	split_diversion(t_data *data, int divert, char *string)
{
	if (divert == 1)
		data->tmp->array = ft_split(string, ':');
	else if (divert == 2)
		data->tmp->array = ft_split(string, ' ');
	if (data->tmp->array == NULL)
		not_perror("check path", NULL, "malloc fail B");
}

/* checking access and creating sub tokens for easy access 
in children res = 3 means we are looking into current directory
so we do not need to check_dir but file muts be checked, this is
 eg so that minishell can run inside minishell*/
int	check_path(char *string, int divert, t_data *all, int x)
{
	char	*suffix;
	size_t	cmd_len;
	int		res;

	cmd_len = 0;
	suffix = NULL;
	res = initial_checks_and_setup(&suffix, &cmd_len, all, x);
	if (res == 3)
	{
		if (check_file(all->tokens->args[x]) == 1)
			return (0);
		all->tmp->filename = ft_strdup(all->tokens->args[x]);
		return (res);
	}
	if (res != 2)
		return (res);
	split_diversion(all, divert, string);
	res = iterate_and_match(suffix, cmd_len, all, x);
	free_array(all->tmp->array);
	if (res == 0)
		return (0);
	return (res);
}
