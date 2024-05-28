/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/28 17:32:04 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)//, char **env)
{
	char	*rl;
	static t_data data;
	static t_env	envs;
	static t_tokens tokens;
	static t_temps tmp;

	(void)argc;
	(void)argv;
	data.tokens = &tokens;
	data.env = &envs;
	data.tmp = &tmp;
	// lst_env(&envs);
	envs = *lst_env(&envs);
	envs = *envs.next; // do not remove, moves node to be the last
/*	if (find_node(&envs, "HOME", &data) == 0)
	{
		envs = *move_list(&envs, "HOME");
		ft_printf("- - - - - - moved into new env node - - - - - - - - \n");
	}
	ft_printf("main.c envs_key: %s\n", envs.key);
	ft_printf("main.c envs_value: %s\n", envs.value);
	ft_printf("- - - - - - - - - - - - - - - - - - \n");*/

	
	ms_init(&data); // filling variables in struct
	// if we want to error handle the return value of ms_init, we can
	while (1)
	{
		set_signals(); 
		rl_on_new_line(); // tells update routine that we are starting a new line, check into this?
		rl = readline(data.prompt); // pastes prompt and reads a line from terminal, returning output
		add_history(rl); // add to history automatically

		if (rl)
		{
			collect_cmd_array(&tokens, rl);
			// find_passage(&data, "PATH", 1);

			// free_nodes(&envs);
			// example of exceve() usage in check_passage
			if (handle_line(data, envs, &tokens, rl) == -1)
				break ;

			// ft_printf("%s\n", rl); //remove
			free_array(tokens.args);
			// free(data.path);
			free(rl);
		}
		if (!rl)
			break ;
	}
  return (0);
}

// int handle_line(t_data data, t_env envs, t_tokens *tokens, char *rl)
// {
// 	char *temp;
// 	char *temp2;
// 	char *cmd;
// 	int i;
	
// 	temp = NULL;
// 	temp2 = NULL;
// 	data.tokens = tokens;
// 	i = -1;
// 	if (ft_strncmp(rl, "cd", 2) != 0)
// 	{
// 		// ft_printf("rl: %s|\n", rl); //remove
// 		cmd = ft_strchcpy(temp, rl, ' ');
// 		// ft_printf("after strchcpy cmd: %s|\n", cmd); //remove
// 		while (cmd && cmd[++i] != '\0')
// 			cmd[i] = ft_tolower(cmd[i]);
// 		// ft_printf("after tolower cmd: %s|\n", cmd); //remove

		
// 		if (ft_strncmp(cmd, "echo", 5) == 0)
// 		{
// 			// ft_printf("added space\n"); //remove
// 			// ft_printf("rl: %s|\n", rl); //remove
// 			rl = ft_memmove(rl, cmd, 4);
// 			// ft_printf("rl: %s|\n", rl); //remove
// 		}
// 	}
// 	else
// 		cmd = ft_strdup("cd "); 
// 	// ft_printf("final cmd: %s|\n", cmd); //remove
// 	if (ft_strncmp(cmd, "exit", 5) == 0) // if exit command is given, exit the program
// 		return (ft_exit(cmd)); // leaks cause it dodes not free cmd
// 	else if (ft_strncmp(cmd, "pwd", 4) == 0)
// 		ft_pwd(&data);
// 	else if (ft_strncmp(cmd, "cd", 2) == 0)
// 		ft_cd(&data, rl);
// 	else if (ft_strncmp(cmd, "echo", 5) == 0)
// 		ft_echo(rl);
// 	else if (ft_strncmp(cmd, "env", 4) == 0)
// 		ft_env(cmd, rl, envs);
// 	else
// 		find_passage(&envs, "PATH", tokens->args);
// 	// {
// 	// 	// ft_printf("AAAAAAA\n");
// 	// 	ft_printf("%s\n", rl);	
// 	// }
// 	if (data.path)
// 		free(data.path);
// 	free(cmd);
// 	return (0);
// }
