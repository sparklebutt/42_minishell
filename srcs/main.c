/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/23 18:29:32 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	printf("aarg\n");	
	char	*rl;
	t_data data;
	static t_env	envs;
	static t_tokens tokens;

//	char *why[]= {"ls", NULL};
//	char *test[] = {"/bin", NULL};
	(void)argc;
	(void)argv;

	lst_env(&envs);

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

			collect_cmd_array(&tokens, rl);
			find_passage(&envs, "PATH", "ls");
			//free_nodes(&envs); //fixes the 11 leaks


//an example on how to use a execvecommand from env no added bs
/*	if (ft_strncmp(rl, "ls", 2) == 0)
    {
      printf("inhere bitch\n");
      execve("/bin/ls", why, env);
     }*/

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
