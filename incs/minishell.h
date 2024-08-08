/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:39 by vkettune          #+#    #+#             */
/*   Updated: 2024/08/07 17:05:45 by araveala         ###   ########.fr       */
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
	char		**env_array; // this is needed for exceves last parameter, eg to run clear
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
char **variable_expansions(t_data *data, t_env *envs, char **args);

int		insert_node(t_env **env_lst, char *key_name, char *value);
// char *fill_old_pwd(t_data *data, t_env *env, char *temp_path);
t_env	*fill_old_pwd(t_data *data, t_env *env, char *temp_path);

char *replace_expansion(t_data *data, t_env *envs, char *arg, int i);
char	*look_if_expansions(t_data *data, t_env *envs, char *arg);
int is_pipe_or_redirect(char *arg);

// OLD STUFF

// main.c
int		main(int argc, char **argv); //, char **env);
/*changed but originals are still safe*/
// int		handle_line(t_data data, t_env envs, t_tokens *tokens);
int		handle_line(t_data data, t_tokens *tokens);

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
void	expansion_parser(t_tokens *tokens, t_data *data);
void	mini_quote_parser(t_tokens *tokens, int i);
int		insert_node(t_env **env_lst, char *key_name, char *value);
int		check_open_quotes(t_tokens *tokens);
int		confirm_action(int du, int si, int d, int s);


char	*clean_quotes(char *string, int len);
int		count_new_len(char *string);
//forking
int		simple_fork(t_data *data);
int		pipe_fork(t_data *data); //int		pipe_set_up(t_data *data);
int		child(t_data *data, int *fds, int prev_fd, int x, int flag);
int		send_to_child(t_data *data, int fds[2], int prev_fd, int x);
// forking utils
int		set_array(t_data *data);// set argumenst array for exceve()
void	set_env_array(t_data *data);
int		dup_fds(t_data *data, int *fds, int prev_fd, int x);
//export parsing
int		validate_it(t_data *data, char *string, int i);
int		check_char(t_data *data, int i, int x);
bool	confirm_expansion(char *string, int len);

//test functions that may or may not be in need of renovation
void	collect_cmd_array(t_data *data, t_tokens *tokens, char *string);
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
void	ft_cd(t_data *data, t_env *envs);
void	ft_echo(char **args);
void	ft_env(t_data *data);//void	ft_env(t_data *data, int fd, int r_w);
void	ft_export(t_data *data);
void	handle_arg(t_data *data, int arg_i, t_tokens *tokens);
char	*find_value(char *arg);
char    *ft_strtrim_front(char *s1, char set);

// handle_line.c
char	*cmd_to_lower(char *rl);
int		is_builtins(char *cmd);
//int		exec_builtins(t_data data, t_env envs, char *cmd);
int		exec_builtins(t_data data, char *cmd, int fd, int r_w);

// fuck about and find out section
/*please remeber to update commenst on if the fucntion is actually usefull or move it into the main fucntions.*/
int send_to_forks(t_data *data);
char	**ft_split_n_keep(char const *s, char c);
#endif
