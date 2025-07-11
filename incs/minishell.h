/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaboom <shaboom@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:39 by vkettune          #+#    #+#             */
/*   Updated: 2025/07/09 14:12:45 by shaboom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define NOT_VALID "not a valid identifier\n"
# define NO_CMD "command not found\n"
# define NO_FILE "no such file or directory\n"
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <stdio.h>
# include <errno.h>
# include <sys/param.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "libft.h"

extern volatile sig_atomic_t	g_interactive_mode;

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
	int		quote;
	char	*here_file;
	
	int		here_fd;
	int		array_count;
	int		pipe_count;
	int		redirect_count;
	int		dollar_count;
	int		out_a_count;
	int		in_a_count;
	
	char	*input_file;
	char	**output_files;


	bool	action;
	bool	in_action;
	bool	redirect_in;
	bool	redirect_out;
	bool	redirect_append;
	bool	ignore_heredoc;
}	t_tokens;

typedef struct s_temps
{
	char	**array;
	char	**exp_array;
	char	**ex_arr;
	char	*filename;
	char	*suffix;
	char	*env_line;
	int		i;
	int		x;
	int		word_len;
	int		check;
	int		flag;
}	t_temps;

typedef struct s_data
{
	int			i;
	int			x;
	int			error_code;
	char		*prompt;
	t_env		*env;
	t_tokens	*tokens;
	t_temps		*tmp;

	int			prev_fd;
	pid_t		child[100];
	int			child_i;
	char		*path;
	bool		simple;
	bool		in_action;
	bool		h_action;
}	t_data;

/* ************************************************************************** */
/*                                                                            */
/*            - - - - - - - - -   PARSING   - - - - - - - - -                 */
/*                                                                            */
/* ************************************************************************** */

//          - - - - - - - - -   parsing_not.c   - - - - - - - - -

int				check_extra_special_echo_case(char **args);
int				collect_cmd_array(t_data *data, t_tokens *tokens, char *string);
int				find_passage(t_data *all, char *string, int divert);

//            - - - - - - - - -   parsers.c   - - - - - - - - -

int				clean_if_multi_dollar_handle(t_data *data, t_tokens *tokens,
					int i);
void			handle_expansion(t_data *data, int len, int i, char *new);
int				expansion_parser_help(t_tokens *tokens, t_data *data, char *new,
					int i);
int				expansion_parser(t_tokens *tokens, t_data *data);

//       - - - - - - - - -   quotes_parsing.c   - - - - - - - - -

int				check_open_quotes(t_tokens *tokens, int s_quote_count,
					int d_quote_count);
char			*clean_quotes(char *string, int len, int x, int y);
int				clean_rest_of_quotes(t_data *data, int i, int len);

//      - - - - - - - - -   check_path.c   - - - - - - - - -

int				check_path(char *string, int divert, t_data *data, int x);

//         - - - - - - - - -   pipe_parsing.c   - - - - - - - - -

int				pipe_collector(t_tokens *tokens, char **array);

//      - - - - - - - - -   expansion_helper.c   - - - - - - - - -

void			simple_flagged(t_data *data, char *new, int len, int i);

//       - - - - - - - - -   prasing_helpers.c   - - - - - - - - -

bool			set_check(char *string, bool ver, int *x, char c);
int				simple_quote_check(char *s, int i);
bool			confirm_expansion(char *string, int len, int x);
int				multi_dollar_handle(t_data *data, t_tokens *tokens, int i);

//      - - - - - - - - -   list_manipulation.c   - - - - - - - - -

int				create_redir_array(t_tokens *tokens);
int				redirect_collector(t_tokens *tokens, char **array, int i,
					int in_count);
int				redirect_helper(t_tokens *tokens, int x);
int				parse_redirections(t_data *data, t_tokens *tokens,
					char **args, int i);

//      - - - - - - - - -   redir_helper.c   - - - - - - - - -

int				is_char_redir(char arg);
int				is_redirect(char *arg);
int				input_helper(t_tokens *tokens, int fd, int i);
int				output_helper(t_tokens *tokens, int fd, int i, int x);

/* ************************************************************************** */
/*                                                                            */
/*              - - - - - - - - -   ENV   - - - - - - - - -                   */
/*                                                                            */
/* ************************************************************************** */

//      - - - - - - - - -   list_manipulation.c   - - - - - - - - -

t_env			*replace_value(t_env *env, char *key, char *new_value);
int				insert_node(t_env **env_lst, char *key_name, char *value);
t_env			*move_list(t_env *envs, char *key);

//        - - - - - - - - -   find_from_env.c   - - - - - - - - -

char			*find_key(char *str);
char			*find_value(char *arg);
char			*find_keys_value(t_env *envs, char *key);
int				find_node_len(t_data *data);
int				find_node(t_env *envs, char *key, t_data *data);

//      - - - - - - - - -   list_manipulation.c   - - - - - - - - -
//      - - - - - - - - -   list_manipulation.c   - - - - - - - - -

// variable_expansions
char			*replace_expansion(t_data *data, t_env *envs, char *arg, int i);
char			*look_if_expans(t_data *data, t_env *envs, char *arg, int flag);

/* ************************************************************************** */
/*                                                                            */
/*              - - - - - - - - -   CMDS   - - - - - - - - -                  */
/*                                                                            */
/* ************************************************************************** */

void			ft_unset(t_env **env, char **args);
int				ft_pwd(t_data *data, t_env *envs);
t_env			*fill_old_pwd(t_data *data, t_env *env, char *temp_path);
void			ft_exit(t_data *data, char *cmd, t_tokens *tokens);
void			ft_cd(t_data *data, t_env *envs);
void			ft_echo(t_data *data, char **args);
void			ft_env(t_env **envs, t_data *data);
void			ft_export(t_data *data);
void			handle_arg(t_data *data, int arg_i, t_tokens *tokens);
char			*ft_strtrim_front(char *s1, char set);
int				check_dir(char *str);

/* ************************************************************************** */
/*                                                                            */
/*              - - - - - - - - -   UTILS   - - - - - - - - -                 */
/*                                                                            */
/* ************************************************************************** */

// error_handling
int				error(char *cmd, char *error);
void			cmd_error(char *cmd, char *arg);
t_env			*call_env_error(char *cmd, char *arg);
int				call_cmd_error(char *cmd, char *arg, char *msg, int ret_value);
void			not_perror(char *cmd, char *arg, char *msg);

// free_things
void			free_array(char **array);
char			*free_string(char *string);
void			free_nodes(t_env *nodes);
char			**free_loop(char **arr, int index);
void			free_stuff(t_data *data, int flag);

// signals
void			here_signal(int sig);
void			handle_sigint(int sig);
void			handle_sigquit(int sig);
void			signal_handler(int sig);
void			set_signals(int sig);

// ft_split_adv
char			**ft_split_adv(char const*s, t_data *data);
size_t			total_words_c(char const *s, char c);

// string_loopers
const char		*exp_loop(char c, int *i, const char *s, int *count);
void			sublen_loop(char c, int *sublen, int *save, const char *s);
int				loop_quotes(t_tokens *tokens, int quote_count, int i, int *x);
void			fancy_loop(const char *s, int *i, char c);
// void			stupid_if_statement(const char *s, int *i, int *words);
int				special_echo_loop(char **args, int *x, int *i);
int				parse_redir_loop(t_data *data, int *i, int *x);
int				redir_collect_loop(char **array, int i, int *count);

void			lol(int *x, int *y);
void			add_redir_count(int token_count, int *count, int *comp_count);

/* ************************************************************************** */
/*                                                                            */
/*              - - - - - - - - -   OTHER   - - - - - - - - -                 */
/*                                                                            */
/* ************************************************************************** */

// handle_line, main & init
int				main(int argc, char **argv);
void			minishell(t_data *data);
int				handle_line(t_data data, t_tokens *tokens, t_env **env);
int				is_builtins(char *cmd);
int				exec_builtins(t_data data, char *cmd, t_env **envs);
t_env			*init(t_data *data);
void			heredoc_loop(t_data *data, int fd, t_tokens *tokens, char *eof);
int				parse_heredoc(char **args);

// forking
int				pipe_fork(t_data *data, int x, int status);
int				child(t_data *data, int *fds, int x, int flag);
int				send_to_child(t_data *data, int fds[2], int x);
void			free_n_exit(t_data *data, int *fds, int flag);

// forking utils
int				set_array(t_data *data);
char			**set_env_array(t_data *data, int i, int x);
int				dup_fds(t_data *data, int *fds, int x);

//parsers.c
void			dollar_counter(char *string, t_tokens *tokens);
char			**ft_split_expansions(t_tokens *tokens, char const *s,
					int index);
int				ft_count_exp_array(const char *s);
int				check_file(char *str);

int				exit_code(int flag, int num);

int				compare_str(char *str1, char *str2);
int				create_file(t_tokens *tokens, int fd);
char			*new_str(char *str, char *value, int start, size_t end);
char			*replace_exitcode(char *arg, int start);

// tester fucntions 
int				print_arr(char **array, char *array_name);
int				open_and_fill_heredoc(t_tokens *tokens);
int				no_dollar_handle(t_tokens *tokens, t_data *data, int i);
int				check_next(char *str, size_t len);
int				null_check(char *str1, t_env *str2, char *str3);
t_env			*create_env_list(char *value, char *key, char *temp);

void			init_adv_loop(t_temps *tmp);
void			stupid_function_3(t_tokens *tokens, int *quote_count,
					int i, int *x);
int				get_word_len(int *check, int *x);
int				fancy_strlen(char const *s, char c, int i);
char			*set_the_string(t_data *data, char *line);

void			set_bools(t_data *data, char *args);
void			execve_fail(t_data *data, char **tmp, int *fds);
void			after_child(t_data *data, int *fds);
int				set_builtin_info(t_data *data, int fds[2], int x);
int				send_to_child_help(t_data *data, int fds[2], int x);
void			close_diff_fds(int *fds, t_data *data, int flag);
int				checks_before_redir(t_data *data, char **args);
char			**fill_env_arr_loop(t_env	*temp2, char **tmp_array, int x,
					char *key_full);
int				handle_absolute_path(t_data *all, int x, char *path);
int				free_string_2(char *str, int ret);
#endif