/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:17:27 by araveala          #+#    #+#             */
/*   Updated: 2024/08/09 09:23:33 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	set_check(char *string, bool ver, int *x, char c)
{
	(*x)++;
	while (string[*x] != c)
	{
		ver = !ver;
		(*x)++;
	}
	return (ver);
}

// similar to quotes_handling (combine them?), maybe add bools into struct
bool	confirm_expansion(char *string, int len)
{
	bool	s;
	bool	d;
	int		x;

	s = false;
	d = false;
	x = 0;
	while (x <= len)
	{
		if (string[x] == '\'')
			set_check(string, s, &x, '\'');
		else if (string[x] == '"')
			set_check(string, d, &x, '"');
		x++;
	}
	return ((d && !s) || (!d && !s));
}

void	handle_expansion(t_data *data, int len, int i, char *new)
{
	t_tokens	*tokens;

	tokens = data->tokens;
	if (ft_strchr(tokens->args[i], '"') != NULL
		|| ft_strchr(tokens->args[i], '\'') != NULL)
	{
		new = clean_quotes(tokens->args[i], len, 0, 0);
		free_string(tokens->args[i]);
		tokens->args[i] = look_if_expansions(data, data->env, new);
	}
	else
		tokens->args[i] = look_if_expansions(data, data->env, tokens->args[i]);
}

void	expansion_parser(t_tokens *tokens, t_data *data)
{
	int			i;
	int			len;
	static char	*new;

	i = 0;
	len = 0;

	while (tokens->args[i])
	{
		len = ft_strlen(tokens->args[i]) - 1; // maybe remove
		if (ft_strchr(tokens->args[i], '$') != NULL)
		{
			if (confirm_expansion(tokens->args[i], len) == true)
			{
				// tokens->args[i] = expand_args(tokens->args[i], data,data->env)
				// add something like this
				handle_expansion(data, len, i, new);
			}
			else
			{
				new = clean_quotes(tokens->args[i], len, 0, 0);
				free_string(tokens->args[i]);
				tokens->args[i] = new;
			}
		}
		i++;
	}
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
			tokens->input_file = strdup(args[i + 1]);
			tokens->redirect_in = 1;
			i++;
		}
		else if ((strcmp(args[i], ">") == 0  || strcmp(args[i], ">>") == 0) && args[i + 1] != NULL)
		{
			printf("args[i]: %s\n", args[i]); // for testing
			tokens->output_file = strdup(args[i + 1]);
			if (strcmp(args[i], ">") == 0)
				tokens->redirect_out = 1;
			else
				tokens->redirect_append = 1;
			i++;
		}
		if (tokens->output_file || tokens->input_file)
		{
			// printf("args[i]: %s\n", args[i]); // for testing
			if (i < 2)
				return (error("redirect", "Syntax error"));
			apply_redirections(tokens, i - 2); // exits program for now
		}
		i++;
	}
	return (0);
}

void	apply_redirections(t_tokens *tokens, int i)
{
	if (tokens->redirect_in)
		redirect_helper(tokens, tokens->input_file, O_RDONLY, i);
	else if (tokens->redirect_out)
		redirect_helper(tokens, tokens->output_file,
			O_WRONLY | O_CREAT | O_TRUNC, i);
	else if (tokens->redirect_append)
		redirect_helper(tokens, tokens->output_file,
			O_WRONLY | O_CREAT | O_APPEND, i);
	exit(0);
}
