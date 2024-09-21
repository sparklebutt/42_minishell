/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:02:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/21 20:53:31 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_char_redir(char arg)
{
	if (arg == '>')
		return (1);
	if (arg == '<')
		return (1);
	return (0);
}

int	is_redirect(char *arg)
{
	if ((arg[0] == '>') || ft_strncmp(arg, ">>", 2) == 0)
		return (3);
	if (ft_strncmp(arg, "<<", 2) == 0)
		return (2);
	if (arg[0] == '<')
		return (1);
	return (0);
}

int	input_helper(t_tokens *tokens, int fd, int i)
{
	if (ft_strncmp(tokens->args[i], "<<", ft_strlen(tokens->args[i]) + 1) == 0)
	{
		tokens->here_file = free_string(tokens->here_file);
		tokens->here_file = ft_strdup(tokens->args[i + 1]);
		tokens->here_check = 1;
	}
	else
	{
		fd = open(tokens->args[i + 1], O_RDONLY);
		if (fd < 0)
		{
			tokens->input_file = free_string(tokens->input_file);
			not_perror(tokens->args[i + 1], NULL, NO_FILE);
			return (-1);
		}
		tokens->input_file = free_string(tokens->input_file);
		tokens->input_file = ft_strdup(tokens->args[i + 1]);
		tokens->redirect_in = 1;
		close(fd);
	}
	return (0);
}

int	output_helper(t_tokens *tokens, int fd, int i, int x)
{
	if (ft_strncmp(tokens->args[i], ">>", ft_strlen(tokens->args[i]) + 1) == 0)
	{
		tokens->output_files[x] = free_string(tokens->output_files[x]);
		tokens->output_files[x] = ft_strdup(tokens->args[i + 1]);
		tokens->redirect_append = 1;
		fd = open(tokens->args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (-1);
		close(fd);
	}
	else
	{
		tokens->output_files[x] = free_string(tokens->output_files[x]);
		tokens->output_files[x] = ft_strdup(tokens->args[i + 1]);
		fd = open(tokens->output_files[x], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (-1);
		close(fd);
		tokens->redirect_out = 1;
	}
	return (0);
}
