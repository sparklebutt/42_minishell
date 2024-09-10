/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/10 20:02:33 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**~~ added error handeling to collect_cmd_array returns 0 on success
 im not sure if this might be more helpfull when handleing exit codes, 
 this is to catch if no infile at the very begining, as our code now creates all files
 at the very begining in parsing, this way we can run error message and not go
 through any further code , exampl cat < no > out ~~**/
void	minishell(t_data *data)
{
	char	*rl;

	while (1)
	{
		//set_signals();
		rl_on_new_line();
		rl = readline(data->prompt);
		add_history(rl);
		if (!rl)
			break ;
		if (rl)
    	{
			if (collect_cmd_array(data, data->tokens, rl) == 0)
				handle_line(*data, data->tokens);
		}
		free_string(rl);
		free_array(data->tokens->args);
		// free_array(data->tokens->output_files); // we are putting something non malloced in here, OR freeing something before this
		// free_array(data->tokens->heredoc); // this needs to be freed somewhere when it is filled properly, needs to be tested
	}
	ft_printf("exit\n");
}

int main(int argc, char **argv)
{
	static t_data data;
	static t_tokens tokens;
	static t_temps tmp;
	
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
