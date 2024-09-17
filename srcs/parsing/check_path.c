/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:50:47 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/17 09:40:04 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	initial_checks_and_setup(char **suffix, size_t *cmd_len, t_data *all, int x)
{
	*cmd_len = ft_strlen(all->tokens->args[x]);
	if (*cmd_len == 0)
		return (0); // why continue at all after this ? 
	if (all->tokens->args[x][0] == '.')
		return (3);
	
	if (all->tokens->args[x][0] == '/')
	{
		// printf("all->tokens->args[x] = %s\n", all->tokens->args[x]);
		return (handle_absolute_path(all, x, NULL), 3);
	}
		
	if (all->tokens->args[x][0] != '/')
	{
		//printf("checking suffix before = %s\n", *suffix); /// after testing this is always null at this stage already
		// *suffix = free_string(*suffix); // in theory this would mean this free does nothing
		//printf("checking suffix after freed = %s\n", *suffix);	
		*suffix = ft_strjoin("/", all->tokens->args[x]);
	}
	if (*suffix == NULL)// || *cmd_len == 0)
	{
		//free_string(*suffix); // if suffix is null there is nothing to free // this removed an issue
		return (0);
	}
	return (2);
}

int	match(t_data *all, DIR *dir, char *suffix, int i)
{
	all->tmp->filename = ft_strjoin(all->tmp->array[i], suffix);
	suffix = free_string(suffix);
	closedir(dir);
	return (1);
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
					return (match(all, dir, suffix, i));
			}
			closedir(dir);
		}
		i++;
	}
	suffix = free_string(suffix);
	return (0);
}

/*~~ divert 1 = PATH, divert 2 = HOME~~*/
static void	split_diversion(t_data *data, int divert, char *string)
{
	if (divert == 1)
		data->tmp->array = ft_split(string, ':');
	else if (divert == 2)
		data->tmp->array = ft_split(string, ' ');
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
	char	*suffix;
	size_t	cmd_len;
	int		res;

	cmd_len = 0;
	//suffix = NULL;
	res = initial_checks_and_setup(&suffix, &cmd_len, all, x);
	// printf("what is res 1? %d\n", res);
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
	// printf("what is res 2? %d\n", res);
	free_array(all->tmp->array);
	if (res == 0)
		return (0);
	return (res);
}
