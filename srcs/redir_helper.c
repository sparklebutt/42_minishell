/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:02:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/10 20:03:22 by vkettune         ###   ########.fr       */
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
	if (ft_strncmp(tokens->args[i], "<<", ft_strlen(tokens->args[i]) + 1) == 0)
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
	free_string(tokens->output_files[x]); // new free
	tokens->output_files[x] = ft_strdup(tokens->args[i + 1]);	
	if (ft_strncmp(tokens->args[i], ">>", ft_strlen(tokens->args[i]) + 1) == 0)
	{
		// free_string(tokens->output_files[x]);
		// tokens->output_files[x] = ft_strdup(tokens->args[i + 1]);	
		tokens->redirect_append = 1;
		fd = open(tokens->args[i + 1], O_WRONLY | O_CREAT | O_APPEND , 0644);
		close(fd);
	}
	else
	{
		// free_string(tokens->output_files[x]);
		// tokens->output_files[x] = ft_strdup(tokens->args[i + 1]);
		// token flushing becuase we re malloc ontop all the time , this could be handled different
		printf("\t\ttoken flush ehre ?? = %s\n", tokens->output_files[x]);
		// malloc fail check with free
		fd = open(tokens->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);	
		close(fd);
		tokens->redirect_out = 1;	
	}
	return (0);
}

