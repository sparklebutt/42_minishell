/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:52 by araveala          #+#    #+#             */
/*   Updated: 2024/08/05 17:29:15 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* please see if its possible to remove simple fork completely and just use this function,
 it is possible we need to change how x is handled to ensure its possible*/

////this test fucntion shows me what fds are open this will help debugging later
/*static void list_open_fds() {
    for (int fd = 0; fd < 1024; fd++) {
        if (fcntl(fd, F_GETFD) != -1) {
            printf("FD %d is open\n", fd);
        }
    }
	}*/

int	child(t_data *data, int *fds, int prev_fd, int x, int flag) // will try to put all fds in array prev_fd = fd[2]
{	
	pid_t	child;
	int		status;

	child = fork();
	if (child == -1)
	{
		ft_printf("errror in first child perror\n");
		return (-1);
	}
	if (child == 0)
	{
		dup_fds(data, fds, prev_fd, x);
		if (flag == 1)
		{
			exec_builtins(*data, data->tokens->args[data->i], 0, 0);
			exit(0);
		}
		else if (flag == 0)
		{
			execve(data->tmp->filename, data->tmp->ex_arr, data->env_array);
			ft_printf("need perror here, exceve failed in pipe fork\n");
			exit(1);
		}
	}
	if (prev_fd != -1)
		close(prev_fd);
	close(fds[1]);
	waitpid(child, &status, 0);
	return (0);
}
// pid is in struct , we can use that 

/*here we try to send to exceve or seperate thing for our builtins*/
int	send_to_child(t_data *data, int fds[2], int prev_fd, int x)
{
	if (is_builtins(data->tokens->args[data->i]) == 1)
	{
		// printf("handle bultin\n");
		child(data, fds, prev_fd, x, 1);
		data->i++;
		while (data->tokens->args[data->i] != NULL)
		{
			/* should check what the arguments are after, if we need to handle them at all at this stage*/
			if (data->tokens->args[data->i][0] == '|')
			{
				data->i++;
				break ;
			}
			data->i++;
		}
	}
	else if (check_path(data->tmp->env_line, 1, data, data->i) != -1)
	{
		set_array(data);
		child(data, fds, prev_fd, x, 0);
		if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] == '|')
			data->i++;
	}
	else
		return (-1);
	return (0); // success
}

/*pipes and forks does not handle bultins yet*/
/*here we loop through and reuse the fds using prev as outr ?linker fd?*/
int	pipe_fork(t_data *data) // rename pipe_set_up for example as this is what it does
{
	int	fds[2];
	int	prev_fd;
	int	x;

	x = 0;
	prev_fd = -1;
	// might need to set env array in functions that manipulate env list
	set_env_array(data);
	while (x <= data->tokens->pipe_count)
	{
		if (data->i > data->tokens->array_count)
		{
			ft_printf("we are somehow out of bounds \n");
			return (-1);
		}
		if (pipe(fds) < 0)
		{
			ft_printf("error in pipe perror needed\n");
			exit(EXIT_FAILURE);
		}
		// eg example Env | grep PATH=
		send_to_child(data, fds, prev_fd, x);
		prev_fd = fds[0]; // saving current pipe read end 
		// close(fds[0]);
		x++;
	}
	free_array(data->env_array);
	close(fds[0]);
	close(fds[1]);	
//	list_open_fds();	
	if (prev_fd != -1)
		close(prev_fd);
	return (0);
}

/* simple forking*/

int	simple_fork(t_data *data)
{
	int	status;

	status = 0;
	data->pid = fork();
	if (data->pid == -1)
	{
		ft_printf("fork error\n");
		exit(1);
	}
	if (data->pid == 0)
	{
		if (execve(data->tmp->filename, data->tmp->ex_arr, data->env_array) == -1)
		{
			ft_printf("exceve fail\n");
			exit(1); // should this be different kind of error handeling
		}
	}
	// free_array(data->env_array);
	waitpid(data->pid, &status, 0);
//	list_open_fds();
	return (0);
}
