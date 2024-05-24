/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:39 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/24 10:58:42 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
#include <stdio.h>
# include <errno.h>
# include <sys/param.h>
# include <sys/wait.h>

# include "libft.h"

typedef struct s_env
{
	char	*key;
	char	*value;
	struct	s_env *next;
	struct	s_env *prev; //might not need due to having a key
}	t_env;

typedef struct s_tokens
{
	char *cmd;
	char **args;

	int	pipe_count;
}			t_tokens;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}	t_cmd;

typedef struct s_data
{
	char	*prompt;
	t_env	*env;
	t_cmd	*cmds;
  t_tokens	*tokens;
	int		pid;
	char *path;
}	t_data;

// args.c
int		args(t_data *data, char *prompt);

// main.c
int		main(int argc, char **argv, char **env);
int	handle_line(t_data data, t_env envs, char *rl);

// signals.c
void	signal_handler(int signo);
void	set_signals(void);

// init.c
void	ms_init(t_data *data);

// env.c
t_env	*env_init(t_data *data, char **env);

t_env	*add_new_node(char *value_in, char *key_in);
void	addnode(t_env **env_list, t_env *node);
void	lst_env(t_env *envs);
void	free_nodes(t_env *nodes);

//test functions that may ormay not be in need of renovation
void	collect_cmd_array(t_tokens *tokens, char *string);
void	check_path_bla(char *string, char *cmd, int flag);
void	find_passage(t_env *envs, char *string, char *cmd);

// cmds.c
int		ft_pwd(t_data *data);
void ft_cd(t_data *data, char *rl);
int ft_exit(char *cmd);
void ft_echo(char *rl);
void handle_quotes(char **str);
void ft_env(char *rl, char *cmd, t_env envs);
char	*trim_start(char *str);

#endif
