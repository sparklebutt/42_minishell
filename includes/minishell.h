/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:56:39 by vkettune          #+#    #+#             */
/*   Updated: 2024/05/22 11:17:42 by vkettune         ###   ########.fr       */
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
	
	char	*value;
}	t_env;

typedef struct s_data
{
	char	*prompt;
	t_env	*env;
	int		pid;
	char *path;
}	t_data;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}	t_cmd;

// args.c
int		args(t_data *data, char *prompt);

// main.c
int		main(int argc, char **argv, char **env);
int	handle_line(t_data data, char *rl);

// signals.c
void	signal_handler(int signo);
void	set_signals(void);

// init.c
void	ms_init(t_data *data, char **env);

// env.c
t_env	*env_init(t_data *data, char **env);

// cmds.c
int		pwd(t_data *data);
int		cd(t_data *data, char *path);
int		echo(t_data *data, char *str);
int		env(t_data *data);
int		export(t_data *data);
int		unset(t_data *data);
int	ft_exit(t_data *data);

#endif