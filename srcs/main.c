/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/09/23 18:15:08 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_interactive_mode;

void	minishell(t_data *data)
{
	char	*rl;
	// CHECK MAKEFILE FOR FUCKING COMMENTS AND CLEAN IT

	while (1)
	{
		set_signals(g_interactive_mode);
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
		data->tokens->input_file = free_string(data->tokens->input_file);
		free_array(data->tokens->output_files);
		data->tokens->output_files = NULL;
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
