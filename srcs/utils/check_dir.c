/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 08:16:04 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/23 11:17:51 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file(char *str)
{
	if (access(str, X_OK) == -1)
		return (1);
	return (0);
}

int	check_dir(char *str)
{
	struct dirent		*dp;
	DIR					*test;

	test = NULL;
	if (access(str, X_OK) == -1)
		return (0);
	else
		test = opendir(str);
	if (test == NULL)
		return (0);
	dp = readdir(test);
	if (dp == NULL)
		return (closedir(test), 0);
	closedir(test);
	return (1);
}

int	find_len(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	while (len > 0)
	{
		if (str[len] == '/')
			break ;
		len--;
	}
	return (len);
}

int	handle_absolute_path(t_data *all, int x, char *path)
{
	size_t	len;

	len = find_len(all->tokens->args[x]);
	path = free_string(path);
	path = ft_calloc(sizeof(char), len + 1);
	path = ft_strncpy(path, all->tokens->args[x], len);
	if (check_dir(path) == 0)
	{
		error("check dir", path);
		path = free_string(path);
		return (0);
	}
	else
	{
		all->tmp->filename = all->tokens->args[x];
		path = free_string(path);
		return (1);
	}
	path = free_string(path);
	return (0);
}
