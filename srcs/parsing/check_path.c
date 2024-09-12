/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:50:47 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/12 18:10:21 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	initial_checks_and_setup(char **suffix, size_t *cmd_len, t_data *all, int x)
{
	*cmd_len = ft_strlen(all->tokens->args[x]);
	if (all->tokens->args[x][0] == '.')
		return (3);
	if (all->tokens->args[x][0] == '/')
		return (handle_absolute_path(all, x, NULL));
	if (all->tokens->args[x][0] != '/')
	{
		free_string(*suffix);
		*suffix = ft_strjoin("/", all->tokens->args[x]);
	}
	if (*suffix == NULL || *cmd_len == 0)
		return (free_extra_return_function(*suffix, 0));
	return (2);
}

int	iterate_and_match(char *suffix, size_t cmd_len, t_data *all, int x)
{
	DIR				*dir;
	struct dirent	*dp;
	int				i;

	dir = NULL;
	dp = NULL;
	i = 0;
	while (all->tmp->array[i])
	{
		if (check_dir(all->tmp->array[i]) == 1)
		{
			dir = opendir(all->tmp->array[i]);
			while ((dp = readdir(dir)) != NULL)
			{
				if (ft_strncmp(dp->d_name, all->tokens->args[x], cmd_len) == 0
					&& ft_strlen(dp->d_name) == cmd_len)
				{
					free_string(all->tmp->filename);
					all->tmp->filename = ft_strjoin(all->tmp->array[i], suffix);
					closedir(dir);
					return (1);
				}
			}
			closedir(dir);
		}
		i++;
	}
	return (0);
}

int	cleanup_and_finalize(char *suffix, t_data *all, int found)
{
	(void)suffix;
	//free_string(suffix);
	free_array(all->tmp->array);
	if (found)
		return (1);
	return (0);
}

/*~~ divert 1 = PATH, divert 2 = HOME~~*/
static void	split_diversion(t_data *data, int divert, char *string)
{
	if (divert == 1)
	{
		free_array(data->tmp->array);
		data->tmp->array = ft_split(string, ':');
	}
	else if (divert == 2)
	{
		free_array(data->tmp->array);
		data->tmp->array = ft_split(string, ' ');
	}
	if (data->tmp->array == NULL)
	{
		printf("temp[i] is null for some reason\n");
		// figure out what kind of error message is needed
	}
}

/*~~ checking access and creating sub tokens for easy access in children
res = 3 means we are looking into current directory so we do not need to check_dir
but file muts be checked, this is eg so that minishell can run inside minishell~~*/
int	check_path(char *string, int divert, t_data *all, int x)
{
	static char	*suffix;
	size_t	cmd_len;
	int		res;
	int		found;

	cmd_len = 0;

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
	found = iterate_and_match(suffix, cmd_len, all, x);
	if (found == 0)
	{
		return (0);
	}
	res = cleanup_and_finalize(suffix, all, found);
	all->tmp->array = NULL;
	return (res);
}