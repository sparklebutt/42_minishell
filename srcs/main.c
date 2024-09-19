/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/19 08:25:14 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_interactive_mode; // = 1 means we are in interactive mode

/**~~ added error handeling to collect_cmd_array returns 0 on success
 im not sure if this might be more helpfull when handleing exit codes, 
 this is to catch if no infile at the very begining, as our code now
 creates all files at the very begining in parsing, this way we can
 run error message and not go through any further code , exampl 
 cat < no > out ~~**/
void	minishell(t_data *data)
{
	char	*rl;

	while (1)
	{
		set_signals();
		g_interactive_mode = 1;
		rl = readline(data->prompt);
		add_history(rl);
		if (!rl)
			break ;
		if (rl)
		{
			if (collect_cmd_array(data, data->tokens, rl) == 0)
				handle_line(*data, data->tokens, &data->env);
		}
		rl = free_string(rl);
		free_array(data->tokens->args);
		free(data->tokens->heredoc);
		data->tokens->input_file = free_string(data->tokens->input_file);
		free_array(data->tokens->output_files);
		data->tokens->output_files = NULL;
		exit_code(1, 0);
	}
	ft_printf("exit\n");
}

int	main(int argc, char **argv)
{
	static t_data		data;
	static t_tokens		tokens;
	static t_temps		tmp;

	(void)argc;
	(void)argv;
	data.tokens = &tokens;
	data.tmp = &tmp;
	data.env = init(&data);
	rl_clear_history();
	minishell(&data);
	free_nodes(data.env);
	return (0);
}
