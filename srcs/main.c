/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/22 14:09:35 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char	*rl;
	t_data data;
	static t_env	envs;
	// int		out;

	(void)argc;
	(void)argv;
	
	lst_env(&envs);//ar added
	while (envs.next != NULL)
	{
		printf("value in envs  = %s\n", envs.value);
		printf("key in envs  = %s\n", envs.key);
		envs = *envs.next;
	}
	free_nodes(&envs);
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
	// free(rl); // ????
	// free(&data); // ????
  return (0);
}

int	handle_line(t_data data, char *rl)
{
	char *temp;
	(void)data;
	(void)rl;
	
	// !! move these into srcs/cmds.c and call the functions from there !!
	if (ft_strncmp(rl, "exit", 5) == 0) // if exit command is given, exit the program
		return (-1);
	if (ft_strncmp(rl, "pwd", 4) == 0 || strncmp(rl, "cd", 2) == 0)
		data.path = getcwd(NULL, 0); // get current working directory
	if (ft_strncmp(rl, "pwd", 4) == 0)
		ft_printf("%s\n", data.path); // print current working directory
	else if (ft_strncmp(rl, "cd", 2) == 0)
	{
		// was testing how it works, THIS IS NOT NEEDED ANYMORE
		ft_printf("old pwd: %s\n", data.path); // print current working directory
		// ft_printf("temp: %s\n", rl); 
		temp = ft_strtrim(rl, "cd ");
		// ft_printf("temp: %s\n", temp);
		temp = ft_strjoin("/", temp);
		// ft_printf("temp: %s\n", temp);
		temp = ft_strjoin(data.path, temp);
		// ft_printf("temp: %s\n", temp);
		chdir(temp);
		data.path = getcwd(NULL, 0);
		ft_printf("new pwd: %s\n", data.path); // print new working directory
	}
	else if (ft_strncmp(rl, "echo ", 5) == 0)
	{
		temp = getenv("USER");
		ft_printf("%s\n", temp);
		// rl = ft_strtrim(rl, "echo ");
		// ft_printf("%s\n", rl); // print echo
	}
	else
		ft_printf("%s\n", rl); // return rl on a new line
	
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
