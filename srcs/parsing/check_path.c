/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:50:47 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/09 18:48:51 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	initial_checks_and_setup(char **suffix, size_t *cmd_len, t_data *all, int x)
{
	*cmd_len = ft_strlen(all->tokens->args[x]);
	if (ft_strchr(all->tokens->args[x], '/'))
		return (handle_absolute_path(all, x, NULL));
	if (all->tokens->args[x][0] != '/')
		*suffix = ft_strjoin("/", all->tokens->args[x]);
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
	free_string(suffix);
	if (all->tokens->pipe_count > 0)
		free_array(all->tmp->array);
	if (found)
		return (1);
	return (0);
}

static void	split_diversion(t_data *data, int divert, char *string)
{
	if (divert == 1) // PATH
		data->tmp->array = ft_split(string, ':');
	else if (divert == 2) // HOME
		data->tmp->array = ft_split(string, ' ');
	if (data->tmp->array == NULL)
	{
		printf("temp[i] is null for some reason\n");
		// figure out what kind of error message is needed
	}
}

int	check_path(char *string, int divert, t_data *all, int x)
{
	char	*suffix;
	size_t	cmd_len;
	int		res;
	int		found;

	suffix = NULL;
	cmd_len = 0;
	res = initial_checks_and_setup(&suffix, &cmd_len, all, x);
	if (res != 2)
		return (res);
	split_diversion(all, divert, string);
	found = iterate_and_match(suffix, cmd_len, all, x);
	res = cleanup_and_finalize(suffix, all, found);
	return (res);
}

// int	check_path(char *string, int divert, t_data *all, int x)
// {
// 	struct dirent	*dp;
// 	DIR				*dir;
// 	char			*suffix;
// 	size_t			cmd_len;
// 	int				i;

// 	i = 0;
// 	suffix = NULL;
// 	cmd_len = ft_strlen(all->tokens->args[x]);
// 	if (ft_strchr(all->tokens->args[x], '/'))
// 	{
// 		if (handle_absolute_path(all, x, NULL) == 0)
// 		{
// 			// error
// 			return (0);
// 		}
// 		else
// 			return (1);
// 	}
// 	if (all->tokens->args[x][0] != '/')
// 		suffix = ft_strjoin("/", all->tokens->args[x]);
// 	//  ft_printf("suffix = %s\n", suffix);
// 	if (suffix == NULL || cmd_len == 0)
// 		return (free_extra_return_function(suffix, 0));
// 	split_diversion(all, divert, string);
// 	while (all->tmp->array[i])
// 	{
// 		if (check_dir(all->tmp->array[i]) == 1)
// 		{
// 			dir = opendir(all->tmp->array[i]);
// 			dp = readdir(dir);
// 			while (dp != NULL)
// 			{
// 				if (ft_strncmp(dp->d_name, all->tokens->args[x], cmd_len) == 0
// 					&& ft_strlen(dp->d_name) == cmd_len)
// 				{
// 					if (all->tmp->array[i] == NULL)
// 						return (-1);
// 					// free_string(all->tmp->filename);
// 					all->tmp->filename = ft_strjoin(all->tmp->array[i], suffix);
// 					free_string(suffix);
// 					if (all->tokens->pipe_count > 0)
// 						free_array(all->tmp->array);
// 					closedir(dir);
// 					return (1);
// 				}
// 				dp = readdir(dir);
// 			}
// 			// closedir(dir); this was causing a leak of some kind
// 		}
// 		i++;
// 	}
// 	closedir(dir);
// 	//	free_extra_return_function(suffix, -1);
// 	collective_free(NULL, suffix, all->tmp->array);
// 	return (0);
// }
