/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 08:16:04 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/18 08:16:34 by vkettune         ###   ########.fr       */
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
