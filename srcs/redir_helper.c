/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:02:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/18 10:14:15 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int input_helper(t_tokens *tokens, int fd, int i)
{
	fd = open(tokens->args[i + 1], O_RDONLY);
	if (fd < 0)
		return (1);
	close (fd);
	if (ft_strncmp(tokens->args[i], "<<", 2) == 0)
	{
		tokens->here_file = free_string(tokens->here_file);
		tokens->here_file = ft_strdup(tokens->args[i + 1]);
		tokens->here_check = 1;
	}
	else
	{
		tokens->input_file = free_string(tokens->input_file);
		tokens->input_file = ft_strdup(tokens->args[i + 1]);
		tokens->redirect_in = 1;
	}
	return (0);
}

int output_helper(t_tokens *tokens, int fd, int i, int x)
{
	if (ft_strncmp(tokens->args[i], ">>", ft_strlen(tokens->args[i]) + 1) == 0)
	{
		tokens->output_files[x] = free_string(tokens->output_files[x]);
		tokens->output_files[x] = ft_strdup(tokens->args[i + 1]);	
		tokens->redirect_append = 1;
		fd = open(tokens->args[i + 1], O_WRONLY | O_CREAT | O_APPEND , 0644);
		if (fd < 0)
			return (1);
		close(fd);
	}
	else
	{
		tokens->output_files[x] = free_string(tokens->output_files[x]);
		tokens->output_files[x] = ft_strdup(tokens->args[i + 1]);
		fd = open(tokens->output_files[x], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (1);
		close(fd);
		tokens->redirect_out = 1;	
	}
	return (0);
}

