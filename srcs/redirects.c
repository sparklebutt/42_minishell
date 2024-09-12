/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:33:22 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/12 12:57:26 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*~~ needed a fucntion that does the same thing as is_redirect but took a char
and returns the count, it is possible i over thank it ~~*/
int is_char_redirect(char arg)
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

int is_redirect(char *arg)
{
	if ((arg[0] == '>') || ft_strncmp(arg, ">>", 2) == 0)
		return (3);
	if (ft_strncmp(arg, "<<", 2) == 0)
		return (2);
	if (arg[0] == '<')
		return (1);
	return (0);
}
/*~~ to collect redirect count as well as collect how many infiles and outfiles we need
, since each pipe will value only 1 ~~*/
int create_redir_array(t_tokens *tokens)
{
	/*~CHANGE ~*/
	// incase we want to create a input array also
	if (tokens->out_array_count > 0)
	{
		free_array(tokens->output_files); // new free
		tokens->output_files = ft_calloc(sizeof(char *), tokens->out_array_count + 1); // we do need + 1
		if (tokens->output_files == NULL)
		{
			printf("malloc error\n");
			return (-1);
		}
		// printf("\t\ttokens out after malloc = %d\n", tokens->out_array_count);
	}
	return (0);
}
/*~~ this has been over complicated for te fear  of needing this data 
i do not think we will need it but its some of the easiest to remove in last moments~~*/
void	redirect_collector(t_tokens *tokens, char **array, int i)
{
	int out_count = 0;
	int in_count = 0;
	
	int	comparison_tool_out = 0;
	int	comparison_tool_in = 0;	
	int in_array_count = 0; // struct
	tokens->out_array_count = 0;
	while (array[i])
	{
		if (array[i][0] == '>' || ft_strncmp(array[i], ">>", 2) == 0)
		{
			if (ft_strlen(array[i]) > 2)//(len > 2)
				if (array[i][2])
					printf("syntax error, too many redirects\n");
			out_count++;
			// handle redirect as last chat / str
		}
		if (array[i][0] == '<')
		{
			if (ft_strlen(array[i]) > 2)//(len > 2)	
				if (array[i][2])
					printf("syntax error, too many redirects\n");
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
	//printf("does this count the right ammount of out files needed out = %d\n", tokens->out_array_count);
	//printf("does this count the right ammount of in files needed in = %d\n", in_array_count);	
	tokens->redirect_count = out_count + in_count;
}

int	redirect_helper(t_tokens *tokens, int x)
{
	int		fd;

	fd = 0;
	//if (!tokens->output_files[x])
	//	return (0);
	//if (tokens->redirect_in == false && tokens->redirect_out == false && tokens->redirect_append == false )
	//	return (0);	
	// dprintf(2, "\t\twhat is our x count = %d and the file is = %s\n", x, tokens->output_files[x]);
	// dprintf(2, "\t\tand the infile is = %s\n", tokens->input_file);
	if (tokens->redirect_append)
		fd = open(tokens->output_files[x], O_WRONLY | O_CREAT | O_APPEND , 0644);
	else if (tokens->redirect_out)
	{
		//dprintf(2, "what the fuck man \n");
		fd = open(tokens->output_files[x], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (fd < 0)
		return (error("redirect", "Failed to open input file MM"));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (error("redirect", "Failed to duplicate fd"));
	close(fd);
	return (0);
}
/*int	reset_redirect_tokens(t_tokens *tokens)
{
	while ()
	{

	}	
}*/
int	parse_redirections(t_data *data, t_tokens *tokens, char **args, int i)
{
	int x;
	int fd;
	int here_i;
	
	fd = 0;
	x = 0;
	here_i = 0;
	tokens->redirect_out = false;
	/*super good spot to reset all redirection things here */
	while (args[i] != NULL)
	{
		// we could have a fucntion return int checks all
		if (tokens->redirect_out == true && args[i][0] == '|')
		{
			// checking if we had a redirect in pipe line if not we dont move x
			x++;
			tokens->redirect_out = 0;
		}
		if (ft_strncmp(tokens->args[i], "<<", 2) == 0)
		{
			heredoc_loop(data, tokens, tokens->args[i + 1]); // run this function
			// create file and move whole of tokens->heredoc there, each divided by a newline
			while(tokens->heredoc[here_i] != 0) // for testing
			{
				// printf("\t\t\theredoc[%d] = %s\n", here_i, tokens->heredoc[here_i]);
				here_i++;
			}
			// delete temp file at the end of minishell loop (or earlier e.g. end of forks, find place)
			i++;
		}
		else if (args[i + 1] != NULL && strcmp(args[i], "<") == 0)
		{
			input_helper(tokens, fd, i);
			i++;
		}
		// what if args[i + 1] == NULL
		else if (args[i + 1] != NULL && (strcmp(args[i], ">>") == 0 || strcmp(args[i], ">") == 0))
		{
			// it was x causing an over right here because the bool was auto true upon second entry
			output_helper(tokens, fd, i, x);
			i++;
		}
		i++;
	}
	if (tokens->out_array_count > 0)
		tokens->redirect_out = 1;
	return (0);
}

