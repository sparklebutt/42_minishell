/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:33:22 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/21 17:56:06 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_redir_array(t_tokens *tokens)
{
	if (tokens->out_a_count > 0)
	{
		free_array(tokens->output_files);
		tokens->output_files = ft_calloc(sizeof(char *),
				tokens->out_a_count + 1);
		if (tokens->output_files == NULL)
			return (-1);
	}
	return (0);
}

int	redir_syntax(char **args, int i, int *out_count, int *in_count)
{
	if (is_char_redir(args[i][0]) != 0)
	{
		if (args[i + 1] == NULL)
		{
			exit_code(1, 2);
			return (not_perror("redirect", NULL, "syntax error\n"), -1);
		}
		if (args[i + 1] != NULL && (args[i + 1][0] == '|'
			|| args[i + 1][0] == '\0' || is_char_redir(args[i + 1][0]) > 0))
			return (not_perror("redirect", NULL, "syntax error\n"), -1);
	}
	if (args[i][0] == '>' || (args[i][0] == '>' && args[i][1] == '>'))
		redir_collect_loop(args, i, out_count);
	if (args[i][0] == '<')
		redir_collect_loop(args, i, in_count);
	return (0);//exit_code(1, 0));
}

int	redirect_collector(t_tokens *tokens, char **args, int i, int in_count)
{
	int	out_count;
	int	comp_out;
	int	comp_in;

	out_count = 0;
	comp_in = 0;
	comp_out = 0;
	while (args[i] != NULL)
	{
		if (redir_syntax(args, i, &out_count, &in_count) != 0)
			return (-1);
		if (args[i][0] == '|' && comp_out < out_count)
			add_redir_count(tokens->out_a_count, &out_count, &comp_out);
		if (args[i][0] == '|' && comp_in < in_count)
			add_redir_count(tokens->in_a_count, &in_count, &comp_in);
		if (args[i + 1] == NULL)
			break ;
		i++;
	}
	if (out_count > 0)
		tokens->out_a_count += 1;
	tokens->redirect_count = out_count + in_count;
	return (0);
}

int	redirect_helper(t_tokens *tokens, int x)
{
	int		fd;
	char	**out_files;

	out_files = tokens->output_files;
	fd = 0;
	if (tokens->redirect_append)
		fd = open(out_files[x], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (tokens->redirect_out && out_files[x] != NULL)
		fd = open(out_files[x], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (error("redirect", "Failed to open input file A"));
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (error("redirect", "Failed to duplicate fd"));
	}
	close(fd);
	return (0);
}

int	parse_redirections(t_data *data, t_tokens *tokens, char **args, int i)
{
	int	x;

	x = 0;
	tokens->redirect_out = false;
	while (args[i] != NULL)
	{
		if (tokens->redirect_out == true && args[i][0] == '|')
		{
			x++;
			tokens->redirect_out = 0;
		}
		if (parse_redir_loop(data, &i, &x) == -1)
		{
			data->tokens->here_file = free_string(data->tokens->here_file);
			free_array(data->tokens->heredoc);
			data->tokens->heredoc = NULL;
			return (-1);
		}
		if (args[i] != NULL)
			i++;
	}
	if (tokens->out_a_count > 0)
		tokens->redirect_out = 1;
	return (0);
}
