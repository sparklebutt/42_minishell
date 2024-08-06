/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/05 17:52:35 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			collect_cmd_array(data->tokens, rl);
			data->tokens->args = variable_expansions(data, data->env, data->tokens->args);
			if (data->tokens->args[0] == NULL)
				break ;
			printf("\t!!! arg[0] = %s\n", data->tokens->args[0]);
			// if (handle_line(*data, *data->env, data->tokens) == -1) <-- removed data->env
/*~~ adjusted because we dont need to carry this env variable here, we also need space in parameters,
pipes need different data to be carried and i susupect we an utalize the same functions with or without pipes ~~*/
			if (handle_line(*data, data->tokens) == -1)			
			{
				ft_printf("error dfghjkl\n");
				break ;
			}
			free_array(data->tokens->args);
			free(rl);
		}
		if (!rl)
			break ;
	}
	ft_printf("exit\n");
}

int main(int argc, char **argv)//, char **env)
{
	/*~~ valgrind was complaing about initilization before main, copilot suggested it had
	  something to do with static variable~~*/
	static t_data data;
	static t_tokens tokens;
	static t_temps tmp;

//	t_data		data;
//	t_tokens	tokens;
//	t_temps		tmp;
	
	(void)argc;
	(void)argv;
	data.tokens = &tokens;
	data.tmp = &tmp;
	data.env = init(&data);
	minishell(&data);
	free_nodes(data.env);
	return (0);
}
