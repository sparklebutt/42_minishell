/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:33:22 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/09 16:17:13 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redirect(char *arg)
{
	if (arg[0] == '>' || ft_strncmp(arg, ">>", 2) == 0)
		return (2);
	if (arg[0] == '<')
		return (1);
	return (0);
}

void	redirect_collector(t_tokens *tokens, char **array)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	printf("THIS IS IN REDIRECT_COLLECTOR\n");
	while (array[i])
	{
		len = ft_strlen(array[i]);
		printf("\t\tarray[i]: %s\n", array[i]);
		if (array[i][0] == '>' || array[i][0] == '<' || ft_strncmp(array[i], ">>", 2) == 0)
		{
			printf("redirect found!\n");
			if (len > 2) // make this work with quotes
				if (array[i][2])
					printf("syntax error, too many redirects\n");
			count++;
			// handle redirect as last chat / str
		}
		i++;
	}
	tokens->redirect_count = count;
}

int	file_open(t_tokens *tokens, char *file, int flags)
{
	int	fd;

	fd = 0;
	if (tokens->redirect_in)
		fd = open(file, flags, 0); // not creating a file, just reading
	else
		fd = open(file, flags, 0644); // 0644 is the default permission for files
	if (fd < 0)
		return (error("redirect", "Failed to open input file"));
	return (fd);
}

void redirect_out(t_tokens *tokens, int i)
{
	i--;
	if (tokens->redirect_out)
	{
		tokens->args[i] = clean_quotes(tokens->args[i],
			ft_strlen(tokens->args[i]), 0, 0);
		printf("%s\n", tokens->args[i]);
	}
	else if (tokens->redirect_append)
	{
		tokens->args[i] = clean_quotes(tokens->args[i],
			ft_strlen(tokens->args[i]), 0, 0);
		printf("%s\n", tokens->args[i]);
	}
}

int	redirect_helper(t_tokens *tokens, char *file, int flags, int i)
{
	int		fd;
	char	*line;

	fd = file_open(tokens, file, flags);
	if (tokens->redirect_in)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (error("redirect", "Failed to duplicate fd"));
		line = get_next_line(fd);
		while (line != NULL)
		{
			printf("%s", line);
			free(line);
			line = get_next_line(fd);
		}
		free(line);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (error("redirect", "Failed to duplicate fd"));
		redirect_out(tokens, i);
	}
	close(fd);
	return (0);
}

int	parse_redirections(t_tokens *tokens, char **args, int i)
{
	while (args[i] != NULL)
	{
		// printf("args[i]: %s\n", args[i]); // for testing
		if (strcmp(args[i], "<") == 0 && args[i + 1] != NULL)
		{
			printf("args[i]: %s\n", args[i]); // for testing
			printf("\t\tFILL REDIRECT FILE\n");
			tokens->input_file = strdup(args[i + 1]);
			tokens->redirect_in = 1;
			i++;
		}
		else if ((strcmp(args[i], ">") == 0  || strcmp(args[i], ">>") == 0) && args[i + 1] != NULL)
		{
			printf("args[i]: %s\n", args[i]); // for testing
			printf("\t\tFILL REDIRECT FILE\n");
			tokens->output_file = strdup(args[i + 1]);
			if (strcmp(args[i], ">") == 0)
				tokens->redirect_out = 1;
			else
				tokens->redirect_append = 1;
			i++;
		}

		//
		// if (tokens->output_file || tokens->input_file)
		// {
		// 	printf("args[i]: %s\n", args[i]); // for testing
		// 	if (i < 2)
		// 		return (error("redirect", "Syntax error"));
			// if (tokens->pipe_count == 0)
			// 	apply_redirections(tokens, i - 2); // exits program for now
		// }
		i++;
	}
	return (0);
}

void	apply_redirections(t_tokens *tokens, int i)
{
	// if (tokens->redirect_in)
	// 	redirect_helper(tokens, tokens->input_file, O_RDONLY, i);
	printf("\t\tTHIS IS IN APPLY_REDIRECTIONS()\n");
	if (tokens->redirect_out)
		redirect_helper(tokens, tokens->output_file,
			O_WRONLY | O_CREAT | O_TRUNC, i);
	else if (tokens->redirect_append)
		redirect_helper(tokens, tokens->output_file,
			O_WRONLY | O_CREAT | O_APPEND, i);
	exit(0);
}

