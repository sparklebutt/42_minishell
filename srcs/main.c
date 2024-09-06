/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/06 14:45:50 by vkettune         ###   ########.fr       */
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
		set_signals();
		rl_on_new_line();
		rl = readline(data->prompt);
		add_history(rl);
		if (rl)
    	{
			if (collect_cmd_array(data, data->tokens, rl) == 0)
			{
				handle_line(*data, data->tokens);
				free_array(data->tokens->args);
				// @@ we need to go through a list of things that need to be freed maybe @@
				free(rl);
			}
		}
		if (!rl)
			break ;
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
	minishell(&data);
	free_nodes(data.env);
	return (0);
}
