/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:31 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/07 15:21:41 by vkettune         ###   ########.fr       */
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
	envs = *lst_env(&envs);
	envs = *envs.next; // do not remove, moves node to be the last ????????
	ms_init(&data); // if we want to error handle the return value of ms_init, we can
	while (1)
	{
		set_signals();
		rl_on_new_line(); // tells update routine that we are starting a new line, check into this?
		rl = readline(data.prompt); // pastes prompt and reads a line from terminal, returning output
		add_history(rl); // add to history automatically

		if (rl)
		{
			collect_cmd_array(&tokens, rl);
			if (tokens.args[0] == NULL)
				break ;
			// example of exceve() usage in check_passage
			if (handle_line(data, envs, &tokens, rl) == -1)
			{
				// free_array(tokens.args);
				break ;
			}
			// ft_printf("%s\n", rl); //remove
			// free_array(tokens.args);
			// free(data.path);
			free(rl);
		}
		if (!rl)
			break ;
	}
	// free_nodes(&envs);
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
