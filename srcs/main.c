/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/21 18:46:35 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char	*rl;
	t_data data;
	int		out;

	(void)argc;
	(void)argv;
	out = init(&data, env); // minishell init
		// copy env to struct
	while (1)
	{
		// deal with signals
		rl = readline(data.prompt);
		if (!rl)
			return (-1);
		add_history(rl); // add to history automatically
		// parsing (play around with this)
			// error handling
			// check commands
			// handle arguments
			// impliment pipes
			ft_printf("%s\n", rl); // return value
		free(rl);
	}
  return (out);
}

// - - - - - TO DO: - - - - - - - - - 

// 1. Implement parsing
// 2. Implement error handling
// 3. Implement command handling
// 4. Implement argument handling
// 5. Implement pipes
// 6. Implement redirection	
// 7. Implement environment variables
// 8. Implement builtins
	// cd
	// echo
	// env
	// export
	// unset
	// exit
	// pwd
	// ls?
	// clear?
// 9. Implement signals
