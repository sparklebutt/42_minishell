/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:02:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/12 17:37:43 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check access to input file and heredoc,
// check how heredoc acts if you don't have access to the eof file

//	if (tokens->redirect_in)
//	{
		// printf("redir in open input rdonly\n");
		// we dont need to open the damn thing
//		fd = open(tokens->input_file, O_RDONLY);
//	}


int input_helper(t_tokens *tokens, int fd, int i)
{
	fd = open(tokens->args[i + 1], O_RDONLY);
	if (fd < 0)
		return (1);
	close (fd);
	if (ft_strncmp(tokens->args[i], "<<", 2) == 0)
	{
		free_string(tokens->here_file); // new free
		tokens->here_file = ft_strdup(tokens->args[i + 1]);
		tokens->here_check = 1;
	}
	else
	{
		free_string(tokens->input_file); // new free
		tokens->input_file = ft_strdup(tokens->args[i + 1]);
		tokens->redirect_in = 1;
	}
	return (0);
}

int output_helper(t_tokens *tokens, int fd, int i, int x)
{
	if (ft_strncmp(tokens->args[i], ">>", ft_strlen(tokens->args[i]) + 1) == 0)
	{
		free_string(tokens->output_files[x]);
		// because we only want the last 1
		tokens->output_files[x] = ft_strdup(tokens->args[i + 1]);	
		tokens->redirect_append = 1;
		fd = open(tokens->args[i + 1], O_WRONLY | O_CREAT | O_APPEND , 0644);
		close(fd);
	}
	else
	{
		free_string(tokens->output_files[x]);
		// because we only want the last 1
		tokens->output_files[x] = ft_strdup(tokens->args[i + 1]);
		fd = open(tokens->output_files[x], O_WRONLY | O_CREAT | O_TRUNC, 0644);	//instead of args + 1
		close(fd);
		tokens->redirect_out = 1;	
	}
	return (0);
}

