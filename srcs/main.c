/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/07/12 15:37:17 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_data *data)
{
	char	*rl;

	while (1)
	{
		// set_signals();
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
			if (handle_line(*data, *data->env, data->tokens) == -1)
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
