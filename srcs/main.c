/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/24 11:08:43 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char	*rl;
	t_data data;
	static t_env	envs;

	(void)argc;
	(void)argv;
	(void)env;
	
	lst_env(&envs); //ar added
	// ft_printf("test\n");
	// while (envs.next != NULL)
	// {
	// 	printf("value in envs  = %s\n", envs.value);
	// 	printf("key in envs  = %s\n", envs.key);
	// 	envs = *envs.next;
	// }
	// free_nodes(&envs);
	ms_init(&data); // filling variables in struct
	// if we want to error handle the return value of ms_init, we can
	while (1)
	{
		set_signals(); // deal with signals here
		rl_on_new_line(); // tells update routine that we are starting a new line, check into this?
		rl = readline(data.prompt); // pastes prompt and reads a line from terminal, returning output
		add_history(rl); // add to history automatically
		if (rl)
		{ 
			if (handle_line(data, envs, rl) == -1) // new line function, prasing and stuff
				break ;
			// free(&data); // ???? do I need to free this too? or after while loop
			free(rl);
		}
		else if (!rl)
			break ;
	}
	if (rl)
		free(rl);
  return (0);
}

int	handle_line(t_data data, t_env envs, char *rl)
{
	char *temp;
	char *temp2;
	char *cmd;
	int i;
	
	// parsing(data, rl);
	
	temp = NULL;
	temp2 = NULL;
	i = -1;
	if (ft_strncmp(rl, "cd", 2) != 0)
	{
		cmd = ft_strchcpy(temp, rl, ' ');
		// ft_printf("after strchcpy cmd: %s|\n", cmd); //remove
		while (cmd && cmd[++i] != '\0')
			cmd[i] = ft_tolower(cmd[i]);
		// ft_printf("after tolower cmd: %s|\n", cmd); //remove

		
		if (ft_strncmp(cmd, "echo", 5) == 0)
		{
			// ft_printf("added space\n"); //remove
			// ft_printf("rl: %s|\n", rl); //remove
			ft_printf("rl: %s|\n", rl); //remove
			rl = ft_memmove(rl, cmd, 4);
			ft_printf("rl: %s|\n", rl); //remove
		}
	}
	else
		cmd = ft_strdup("cd "); 
	// ft_printf("final cmd: %s|\n", cmd); //remove
	if (ft_strncmp(cmd, "exit", 5) == 0) // if exit command is given, exit the program
		return (ft_exit(cmd)); // leaks cause it dodes not free cmd
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ft_pwd(&data);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		ft_cd(&data, rl);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		ft_echo(rl);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(cmd, rl, envs);
	else
		ft_printf("%s\n", rl); // return rl on a new line
	if (data.path)
		free(data.path);
	free(cmd);
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
