/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:39 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/13 18:47:56 by araveala         ###   ########.fr       */
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
	int		quote; // 1 = single, 2 = double

	int		array_count;
	int		pipe_count;
	int		redirect_count;

	char	*input_file;   // For < redirection
	char	*output_file;  // For > and >> redirection
	bool	redirect_in;
	bool	redirect_out;
	bool	redirect_append;
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
	char		**env_array; // this is needed for exceves last parameter, eg to run clear
	t_cmd		*cmds;
	t_tokens	*tokens;
	t_temps		*tmp;
	int			pid;
	char		*path;
}	t_data;

// PARSING - - - - - - - - -
void	pipe_collector(t_tokens *tokens, char **array);
void	expansion_parser(t_tokens *tokens, t_data *data);
int	check_open_quotes(t_tokens *tokens, int s_quote_count, int d_quote_count);
char	*clean_quotes(char *string, int len, int x, int y);
int		count_new_len(char *string);
int	handle_absolute_path(t_data *all, int x, char *path);

void	collect_cmd_array(t_data *data, t_tokens *tokens, char *string);
int		check_path(char *string, int divert, t_data *all, int x);
int		find_passage(t_data *all, char *string, int divert);
int		parse_redirections(t_tokens *tokens, char **args, int i);
void	apply_redirections(t_tokens *tokens);
void	redirect_collector(t_tokens *tokens, char **array);
int is_redirect(char *arg);

// ENV - - - - - - - - -

// list manipulation
t_env	*replace_value(t_env *env, char *key, char *new_value);
int		insert_node(t_env **env_lst, char *key_name, char *value);
t_env	*move_list(t_env *envs, char *key);

// find from env
char	*find_key(char *str);
char	*find_value(char *arg); // with = e.g. in export
char	*find_keys_value(t_env *envs, char *key); // from key value from env
int		find_node_len(t_data *data); // how many nodes
int		find_node(t_env *envs, char *key, t_data *data); // does node with x key exist in env

// variable expansions
char *replace_expansion(t_data *data, t_env *envs, char *arg, int i);
char	*look_if_expansions(t_data *data, t_env *envs, char *arg);

// CMDS - - - - - - - - -
void	ft_unset(t_env *env, char *key_name);
int		ft_pwd(t_data *data, t_env *envs);
t_env	*fill_old_pwd(t_data *data, t_env *env, char *temp_path);
int		ft_exit(char *cmd, t_tokens *tokens); 
void	ft_cd(t_data *data, t_env *envs);
void	ft_echo(char **args);
void	ft_env(t_data *data);
void	ft_export(t_data *data);
void	handle_arg(t_data *data, int arg_i, t_tokens *tokens);
char	*ft_strtrim_front(char *s1, char set);
int		check_dir(char *str);

// UTILS - - - - - - - - -

// error_handling
int		error(char *cmd, char *error);
void	cmd_error(char *cmd, char *arg);
t_env	*call_env_error(char *cmd, char *arg);
int		call_cmd_error(char *cmd, char *arg, char *msg, int ret_value);
void	collective_free(char *str1, char *str2, char **array);

// free things
void	free_array(char **array);
void	free_string(char *string);
int		free_extra_return_function(char *str, int ret_val);
void	free_nodes(t_env *nodes);

// signals
void	signal_handler(int signo);
void	set_signals(void);

// ft_split_adv
char	**ft_split_adv(char const*s, char c);
size_t	total_words_c(char const *s, char c);

// OTHER - - - - - - - - -

// handle_line, main & init
int		main(int argc, char **argv);
void	minishell(t_data *data);
int		handle_line(t_data data, t_tokens *tokens);
int		is_builtins(char *cmd);
int		exec_builtins(t_data data, char *cmd);
t_env	*init(t_data *data);
t_env	*create_env_list(t_data *data);

// forking
int		simple_fork(t_data *data);
int		pipe_fork(t_data *data);
int		child(t_data *data, int *fds, int prev_fd, int x, int flag);
int		send_to_child(t_data *data, int fds[2], int prev_fd, int x);
int send_to_forks(t_data *data);

// forking utils
int		set_array(t_data *data);
void	set_env_array(t_data *data);
int		dup_fds(t_data *data, int *fds, int prev_fd, int x);
bool	confirm_expansion(char *string, int len);

// newly added functions seperate for clarity
//parsers.c
int		simple_quote_check(char *s, int i);
int is_char_redirect(char arg);
#endif
