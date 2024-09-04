/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:33:22 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/04 18:08:03 by araveala         ###   ########.fr       */
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
		return (2);
	if (arg[0] == '<')
		return (1);
	return (0);
}
/*~~ to collect redirect count as well as collect how many infiles and outfiles we need
, since each pipe will value only 1 ~~*/
void create_redir_array(t_tokens *tokens)
{
//	int i;

//	i = 0;
	tokens->output_files = ft_calloc(sizeof(char *), tokens->pipe_count + 1);
	if (tokens->output_files == NULL)
	{
		printf("malloc error\n");
		// do we need to free anything malloced up to this point
		exit(1);
	}
	// calloc nulls them	
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

int	redirect_helper(t_tokens *tokens, int x) //t_data *data
{
	int		fd;

	fd = 0;	
//	if (tokens->redirect_in)
//	{
		// printf("redir in open input rdonly\n");
		// we dont need to open the damn thing
//		fd = open(tokens->input_file, O_RDONLY);
//	}
	if (tokens->output_files[x] == NULL)
		return (0);
	if (tokens->redirect_append)
		fd = open(tokens->output_files[x], O_WRONLY | O_CREAT | O_APPEND , 0644);
	else if (tokens->redirect_out)
	{
		//printf("is file right? = %s\n", tokens->output_files[x]);		
		fd = open(tokens->output_files[x], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (fd < 0)
		return (error("redirect", "Failed to open input file MM"));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (error("redirect", "Failed to duplicate fd"));
	close(fd);
	return (0);
}

int	parse_redirections(t_tokens *tokens, char **args, int i)
{
	int x = 0; //syntax
	int fd = 0; //syntax
	
	while (args[i] != NULL)
	{
		if (args[i][0] == '|')
			x++;
		if (strcmp(args[i], "<") == 0 && args[i + 1] != NULL)
		{
			fd = open(tokens->args[i + 1], O_RDONLY);
			if (fd < 0)
				return (1);	// i assume exit code will have to be 1 //exit(1);
			close (fd);
			tokens->input_file = strdup(args[i + 1]);
			// this might need to be an array too
			tokens->redirect_in = 1;
			i++;
		}
		// if we sepearte all of these we could manage malloc fails better?
		else if ((strcmp(args[i], ">>") == 0 || strcmp(args[i], ">") == 0) && args[i + 1] != NULL)
		{
			if (strcmp(args[i], ">>") == 0)
			{
				tokens->output_files[x] = ft_strdup(args[i + 1]);	
				tokens->redirect_append = 1;
				fd = open(tokens->args[i + 1], O_WRONLY | O_CREAT | O_APPEND , 0644);
				close(fd);
			}
			else
			{
				tokens->output_files[x] = ft_strdup(args[i + 1]);
				// token flushing becuase we re malloc ontop all the time , this could be handled different
				printf("token flush ehre ?? = %s\n", tokens->output_files[x]);
				// malloc fail check with free
				fd = open(tokens->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);	
				close(fd);
				tokens->redirect_out = 1;	
			}
			i++;
		}
		i++;
	}
	return (0);
}

/*~~ i feel this function does not have a purpose could we use it to do error handeling ~~*/
void	apply_redirections(t_data *data, t_tokens *tokens, int x)
{	
	if (data->i == 100)
		printf("A"); // we can use some data for error checking?
	if (tokens->redirect_in)
	{
		redirect_helper(tokens, x);
	}
	else if (tokens->redirect_out)
	{
		redirect_helper(tokens, x);
	}
	else if (tokens->redirect_append)
	{
		redirect_helper(tokens, x);
	}
}

