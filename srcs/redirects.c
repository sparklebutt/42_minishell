/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:33:22 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/14 11:55:42 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*~~ needed a fucntion that does the same thing as is_redirect but took a char
and returns the count, it is possible i over thank it ~~*/
int is_char_redirect(char arg)
{
//	if (arg == '>' && arg + 1 == '>')
//		return (2);
//	if (arg == '<' && arg + 1 == '<')
//		return (2);
	if (arg == '>')
		return (1);
	if (arg == '<')
		return (1);
	return (0);
}

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
	// printf("THIS IS IN REDIRECT_COLLECTOR\n");
	while (array[i])
	{
		len = ft_strlen(array[i]);
		// printf("\t\tarray[i]: %s\n", array[i]);
		if (array[i][0] == '>' || array[i][0] == '<' || ft_strncmp(array[i], ">>", 2) == 0)
		{
			// printf("redirect found!\n");
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

int	redirect_helper(t_tokens *tokens)
{
	int		fd;
	char *test;

	test = NULL;
	fd = 0;
	if (tokens->redirect_in)
		fd = open(tokens->input_file, O_RDONLY);
	else if (tokens->redirect_append)
		fd = open(tokens->output_file, O_WRONLY | O_CREAT | O_APPEND , 0644);
	else if (tokens->redirect_out)
		fd = open(tokens->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (error("redirect", "Failed to open input file"));
	if (dup2(fd, STDOUT_FILENO) == -1)// && tokens->pipe_count == 0) // trying to avoid dubble duping in pipes
		return (error("redirect", "Failed to duplicate fd"));
	close(fd);
	return (0);
}

int	parse_redirections(t_tokens *tokens, char **args, int i)
{
	while (args[i] != NULL)
	{
		if (strcmp(args[i], "<") == 0 && args[i + 1] != NULL)
		{
			tokens->input_file = strdup(args[i + 1]);
			tokens->redirect_in = 1;
			i++;
		}
		else if ((strcmp(args[i], ">>") == 0 || strcmp(args[i], ">") == 0) && args[i + 1] != NULL)
		{
			tokens->output_file = strdup(args[i + 1]);
			if (strcmp(args[i], ">>") == 0)
				tokens->redirect_append = 1;
			else
				tokens->redirect_out = 1;
			i++;
		}
		i++;
	}
	return (0);
}

void	apply_redirections(t_tokens *tokens)
{
	if (tokens->redirect_in)
		redirect_helper(tokens);
	else if (tokens->redirect_out)
		redirect_helper(tokens);
	else if (tokens->redirect_append)
		redirect_helper(tokens);
}

