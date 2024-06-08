/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:39 by vkettune          #+#    #+#             */
/*   Updated: 2024/06/08 16:04:32 by vkettune         ###   ########.fr       */
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
	char			*key;
	char			*value;
	struct s_env	*head; // not needed
	struct s_env	*next;
	struct s_env	*prev; // not needed
}	t_env;

typedef struct s_tokens
{
	char	*cmd;
	char	**args;

	int		array_count;
	int		pipe_count;
}	t_tokens;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}	t_cmd;

typedef struct s_temps
{
	char	**array;
	char	*ex_arr[4];
	char	*filename;
	char	*suffix;// do we need multiple different ones
	char	*env_line;
	int		i;
}	t_temps;

typedef struct s_data
{
	char		*prompt;
	t_env		*env;
	t_cmd		*cmds;
	t_tokens	*tokens;
	t_temps		*tmp;
	int			pid;
//	char		*env_line;
	char		*path;
}	t_data;

// char *handle_arg(char *arg);

// args.c
int		args(t_data *data, char *prompt);

// main.c
int		main(int argc, char **argv); //, char **env);
int		handle_line(t_data data, t_env envs, t_tokens *tokens, char *rl);
// int	handle_line(t_data data, t_env envs, t_tokens *tokens, char *line);

// signals.c
void	signal_handler(int signo);
void	set_signals(void);

// init.c
void	ms_init(t_data *data);

// env.c
t_env	*env_init(t_data *data, char **env);
t_env	*add_new_node(char *value_in, char *key_in);
t_env	*lst_env(void);
t_env	*move_list(t_env *envs, char *key);
void	addnode(t_env **env_list, t_env *node);
void	free_nodes(t_env *nodes);
int		error(char *cmd, char *error);
int		find_node(t_env *envs, char *key, t_data *data);

//parsers
void	pipe_collector(t_tokens *tokens, char **array);
void	mini_parser(t_tokens *tokens, int i, int x);
int insert_node(t_env **env_lst, char *key_name, char *value);

//export parsing
int	validate_it(t_data *data, char *string, int i);
int	check_char(t_data *data, int i, int x);

//test functions that may ormay not be in need of renovation
void	collect_cmd_array(t_tokens *tokens, char *string);
int	check_path(char *string, int divert, t_data *all);
int	find_passage(t_data *all, char *string, int divert);
void	free_array(char **array);
void	free_string(char *string);
char	**ft_split_adv(char const*s, char c);
char	*find_key_from_envs(t_env *envs, char *key);
size_t	total_words_c(char const *s, char c);

// cmds.c
int		ft_pwd(t_data *data);
int		ft_exit(char *cmd);
char	*trim_start(char *str);
void	ft_cd(t_data *data, t_env *envs, char *rl);
void	ft_echo(char *rl);
void	handle_quotes(char **str);
void	ft_env(t_data *data);
void	ft_export(t_data *data);
void	handle_arg(t_data *data, int arg_i, t_tokens *tokens);
char *find_value(char *arg);
char    *ft_strtrim_front(char *s1, char set);

// handle_line.c
char	*cmd_to_lower(char *rl);
int		is_builtins(char *cmd);
int		exec_builtins(t_data data, t_env envs, char *rl, char *cmd);

#endif
