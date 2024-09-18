/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:33:22 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/18 16:57:07 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*~~ needed a fucntion that does the same thing as is_redirect but took a char
and returns the count, it is possible i over thank it ~~*/
int	is_char_redir(char arg)
{
	if (arg == '>' && arg + 1 == '>')
		return (2);
	if (arg == '<' && arg + 1 == '<')
		return (2);
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

/*~~ to collect redirect count as well as collect how many infiles and outfiles
 we need, since each pipe will value only 1 ~~*/
int	create_redir_array(t_tokens *tokens)
{
	if (tokens->out_array_count > 0)
	{
		free_array(tokens->output_files);
		tokens->output_files = ft_calloc(sizeof(char *), tokens->out_array_count + 1);
		if (tokens->output_files == NULL)
			return (-1);
	}
	return (0);
}
/*~~ this has been over complicated for te fear  of needing this data 
i do not think we will need it but its some of the easiest to remove in last moments~~*/
int	redirect_collector(t_tokens *tokens, char **array, int i)
{
	int out_count = 0;
	int in_count = 0;
	
	int	comparison_tool_out = 0;
	int	comparison_tool_in = 0;	
	int in_array_count = 0; // struct
	tokens->out_array_count = 0;
	while (array[i])
	{
		if (is_char_redir(tokens->args[i][0]) != 0)
		{
			if (tokens->args[i + 1] == NULL)
				return (not_perror("redirect", NULL, "synntax error\n"), -1);
			if (tokens->args[i + 1] != NULL && (tokens->args[i + 1][0] == '|'
				|| tokens->args[i + 1][0] == '\0' || is_char_redir(tokens->args[i + 1][0]) > 0))
			// {
			// 	if (tokens->args[i + 1][0] == '|' || tokens->args[i + 1][0] == '\0' || is_char_redir(tokens->args[i + 1][0]) > 0)
					return (not_perror("redirect", NULL, "synntax error\n"), -1);
			// }
		}
		// eg echo > echo > > echo > |
		if (array[i][0] == '>' || (array[i][0] == '>' && array[i][1] == '>'))
		{
			if (ft_strlen(array[i]) > 2)
				if (array[i][2])
					printf("B syntax error, too many redirects\n");
			out_count++;
			// handle redirect as last chat / str
		}
		if (array[i][0] == '<')
		{
			if (ft_strlen(array[i]) > 2)//(len > 2)	
				if (array[i][2])
					printf("A syntax error, too many redirects\n");
			in_count++;
			// handle redirect as last chat / str
		}
		if (array[i][0] == '|')
		{
			// maybe these could pass com tools as pointers and run this as a seperate function
			// not sure if we need to collect append data or if collectiion of in is needed. 
			if (comparison_tool_out < out_count)
			{
				tokens->out_array_count++;
				comparison_tool_out = out_count;
			}
			if (comparison_tool_in < in_count)
			{
				in_array_count++;
				comparison_tool_in = in_count;
			}
		}
		i++;
	}
	if (out_count > 0)
		tokens->out_array_count += 1;	
	tokens->redirect_count = out_count + in_count;
	return (0);
}

int	redirect_helper(t_tokens *tokens, int x)
{
	int	fd;

	fd = 0;
	if (tokens->redirect_append)
		fd = open(tokens->output_files[x], O_WRONLY | O_CREAT | O_APPEND , 0644);
	else if (tokens->redirect_out)
		fd = open(tokens->output_files[x], O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	int x;
	int fd;
	
	fd = 0;
	x = 0;
	tokens->redirect_out = false;
	/*super good spot to reset all redirection things here */
	while (args[i] != NULL)
	{
		if (tokens->redirect_out == true && args[i][0] == '|')
		{
			x++;
			tokens->redirect_out = 0;
		}
		parse_redir_loop(data, &i, &x);
		if (args[i] != NULL)
			i++;
	}
	if (tokens->out_array_count > 0)
		tokens->redirect_out = 1;
	return (0);
}
