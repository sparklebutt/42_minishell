/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:39 by vkettune          #+#    #+#             */
/*   Updated: 2024/07/12 15:09:33 by araveala         ###   ########.fr       */
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
# include <stdbool.h>

# include "libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
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
	char	*suffix;
	char	*env_line;
	int		i;
}	t_temps;

typedef struct s_data
{
	int			i;
	char		*prompt;
	t_env		*env;
	t_cmd		*cmds;
	t_tokens	*tokens;
	t_temps		*tmp;
	int			pid;
	char		*path;
}	t_data;

t_env	*init(t_data *data);
void	minishell(t_data *data);
void	cmd_error(char *cmd, char *arg);
t_env	*call_env_error(char *cmd, char *arg);

t_env	*create_env_list(void);
int		call_cmd_error(char *cmd, char *arg, char *msg, int ret_value);
void	collective_free(char *str1, char *str2, char **array);

char	*find_key(char *str);
char	*find_value(char *arg);
char	*find_keys_value(t_env *envs, char *key);
t_env	*replace_value(t_env *env, char *key, char *new_value);
int		check_dir(char *str);


int		insert_node(t_env **env_lst, char *key_name, char *value);
// char *fill_old_pwd(t_data *data, t_env *env, char *temp_path);
t_env	*fill_old_pwd(t_data *data, t_env *env, char *temp_path);

// OLD STUFF

// main.c
int		main(int argc, char **argv); //, char **env);
int		handle_line(t_data data, t_tokens *tokens, char *rl);
int		handle_pipe_line(t_data data, t_env envs, t_tokens *tokens, char *rl);
// signals.c
void	signal_handler(int signo);
void	set_signals(void);

// init.c
t_env	*init(t_data *data);

// env.c
//free things
int		free_extra_return_function(char *str, int ret_val);
void		free_array_2(char **array, int x);
// t_env	*lst_env(void);
t_env	*move_list(t_env *envs, char *key);
void	free_nodes(t_env *nodes);
int		error(char *cmd, char *error);
int		find_node(t_env *envs, char *key, t_data *data);

//parsers
void	pipe_collector(t_tokens *tokens, char **array);
void	mini_parser(t_tokens *tokens, int i, int x);
void	expansion_parser(t_tokens *tokens);
void	mini_quote_parser(t_tokens *tokens, int i);
int		insert_node(t_env **env_lst, char *key_name, char *value);
int		check_open_quotes(t_tokens *tokens);
int		confirm_action(int du, int si, int d, int s);

int		set_array(t_data *data, int x);
char	*clean_quotes(char *string, int len);
int		count_new_len(char *string);
//forking
int		simple_fork(t_data *data);
int		pipe_fork(t_data *data, int i);
int		children(t_data *data, int fds[2]);
//export parsing
int		validate_it(t_data *data, char *string, int i);
int		check_char(t_data *data, int i, int x);
void	confirm_expansion(char *string, int len);

//test functions that may or may not be in need of renovation
void	collect_cmd_array(t_tokens *tokens, char *string);
int		check_path(char *string, int divert, t_data *all, int x);
int		find_passage(t_data *all, int i, char *string, int divert);
void	free_array(char **array);
void	free_string(char *string);
char	**ft_split_adv(char const*s, char c);
char	*find_key_from_envs(t_env *envs, char *key);
size_t	total_words_c(char const *s, char c);

// cmds.c
int		ft_pwd(t_data *data, t_env *envs);
int		ft_exit(char *cmd, t_tokens *tokens); // t_data *data, 
char	*trim_start(char *str);
void	ft_cd(t_data *data, t_env *envs, int i);
void	ft_echo(char *rl);
void	handle_quotes(char **str);
void	ft_env(t_data *data);
void	ft_export(t_data *data);
void	handle_arg(t_data *data, int arg_i, t_tokens *tokens);
char	*find_value(char *arg);
char    *ft_strtrim_front(char *s1, char set);

// handle_line.c
char	*cmd_to_lower(char *rl);
int		is_builtins(char *cmd);
int		exec_builtins(t_data data, char *rl, char *cmd, int i);

#endif
