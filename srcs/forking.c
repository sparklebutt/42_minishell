/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:52 by araveala          #+#    #+#             */
/*   Updated: 2024/08/09 16:13:30 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// this test fucntion shows me what fds are open this will help debugging later
/*static void list_open_fds()
{
	for (int fd = 0; fd < 1024; fd++)
	{
		if (fcntl(fd, F_GETFD) != -1)
		{
			printf("FD %d is open\n", fd);
		}
	}
}*/

 // will try to put all fds in array prev_fd = fd[2]
int	child(t_data *data, int *fds, int prev_fd, int x, int flag)
{	
	pid_t	child;
	int		status;

	child = fork();
	if (child == -1)
		return (error("fork", "first child failed"));
	if (child == 0)
	{
		if (flag == 2)
		{
			apply_redirections(data->tokens, data->i - 2);
			exit(0);
		}
		dup_fds(data, fds, prev_fd, x);
		if (flag == 1)
		{
			exec_builtins(*data, data->tokens->args[data->i]);
			exit(0);
		}
		else if (flag == 0)
		{
			execve(data->tmp->filename, data->tmp->ex_arr, data->env_array);
			ft_printf("need perror here, exceve failed in pipe fork\n");  // change error message
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
int	send_to_child(t_data *data, int fds[2], int prev_fd, int x)
{
	if (is_redirect(data->tokens->args[data->i]))	
	{
		child(data, fds, prev_fd, x, 2);
		data->i++;
		while (data->tokens->args[data->i] != NULL)
		{
			if (data->tokens->args[data->i][0] == '>') // add other cases
			{
				data->i++;
				break ;
			}
			data->i++;
		}
	}
	else if (is_builtins(data->tokens->args[data->i]) == 1) {
		child(data, fds, prev_fd, x, 1);
		data->i++;
		while (data->tokens->args[data->i] != NULL)
		{
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
	return (0);
}

int	pipe_fork(t_data *data)
{
	int	fds[2];
	int	prev_fd;
	int	x;

	x = 0;
	prev_fd = -1;
	set_env_array(data);
	while (x <= data->tokens->pipe_count)
	{
		if (data->i > data->tokens->array_count)
			return error("fork", "we are somehow out of bounds");
		if (pipe(fds) < 0) {
			error("fork", "error in pipe perror needed");
			exit(EXIT_FAILURE);
		} // eg example Env | grep PATH=
		send_to_child(data, fds, prev_fd, x);
		prev_fd = fds[0];
		x++;
	}
	free_array(data->env_array);
	close(fds[0]);
	close(fds[1]);//	add list_open_fds(); ?
	if (prev_fd != -1)
		close(prev_fd);
	return (0);
}

int	simple_fork(t_data *data)
{
	int	status;

	status = 0;
	printf("THIS IN SIMPLE FORK\n");
	// this exits the project when tested, does correct thing though
	// if (data->pid == 0 && is_redirect(data->tokens->args[data->i]) >= 1)
	// {
	// 	printf("REDIRECTS EXIST\n");
	// 	data->pid = fork();
	// 	if (data->pid == -1)
	// 	{
	// 		ft_printf("fork error\n"); // change error message
	// 		exit(1);
	// 	}
	// 	apply_redirections(data->tokens, data->i);
	// 	exit(1);
	// }
	data->pid = fork();
	if (data->pid == -1) {
		ft_printf("fork error\n"); // change error message
		exit(1);
	} // this stays in the loop, but prints everything else BUT what it should in the file
	if (data->pid == 0 && is_redirect(data->tokens->args[data->i]) >= 1)
	{
		printf("REDIRECTS EXIST\n");
		apply_redirections(data->tokens, data->i);
		printf("I love you\n");
		exit(1);
	}
	else if (data->pid == 0)
		if (execve(data->tmp->filename, data->tmp->ex_arr, data->env_array) == -1) {
			ft_printf("exceve fail\n");
			exit(1); // should this be different kind of error handeling
		}
	waitpid(data->pid, &status, 0);
//	list_open_fds();
	return (0);
}
