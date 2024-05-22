/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/22 13:47:35 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char	*rl;
	t_data data;

	(void)argc;
	(void)argv;
	ms_init(&data, env); // filling variables in struct
	// if we want to error handle the return value of ms_init, we can
	while (1)
	{
		set_signals(); // deal with signals here
		rl_on_new_line(); // tells update routine that we are starting a new line, check into this?
		rl = readline(data.prompt); // pastes prompt and reads a line from terminal, returning output
		add_history(rl); // add to history automatically
		if (rl)
		{ 
			if (handle_line(data, rl) == -1) // new line function, prasing and stuff
				break ;
			// free(&data); // ???? do I need to free this too? or after while loop
			free(rl);
		}
		else if (!rl)
			break ;
	}
	if (rl)
		free(rl);
	// free(rl); // ????
	// free(&data); // ????
  return (0);
}

int	handle_line(t_data data, char *rl)
{
	char *temp;
	char *temp2;
	(void)data;
	(void)rl;
	
	// parsing(data, rl);
	temp = NULL;
	temp2 = NULL;
	// !! move these into srcs/cmds.c and call the functions from there !!
	if (ft_strncmp(rl, "exit", 5) == 0) // if exit command is given, exit the program
		return (-1);
	if (ft_strncmp(rl, "pwd", 4) == 0)
		ft_pwd(&data);
	else if (ft_strncmp(rl, "cd", 2) == 0)
		ft_cd(&data, rl);
	else if (ft_strncmp(rl, "echo ", 5) == 0)
	{
		temp = getenv("USER");
		ft_printf("%s\n", temp);
		// rl = ft_strtrim(rl, "echo ");
		// ft_printf("%s\n", rl); // print echo
	}
	else
		ft_printf("%s\n", rl); // return rl on a new line
	if (data.path)
		free(data.path);
	// if (temp)
	// 	free(temp);
	// parsing
	// error handling
	// check commands (started)
	// handle arguments
	// impliment pipes
	return (0);
}

// - - - - - TO DO: - - - - - - - - - 

// - - - - main func (done, needs work) - - - -
// - - - - init struct (done) - - - -
// - - - - history (done) - - - -
// - - - - signals (started)
// parsing
	// error handling
	// - - - - command handling (started)
	// argument handling
	// pipes
	// redirection
	// environment variables
	// - - - - builtins (started)
		// - - - - cd (done) - - - -
		// - - - - echo (started)
		// env
		// export
		// unset
		// - - - - exit (done) - - - -
		// - - - - pwd (done) - - - -
