/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:52 by araveala          #+#    #+#             */
/*   Updated: 2024/07/12 15:10:33 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_array(t_data *data, int x)
{
	int flag;
	flag = 0;

	data->tmp->ex_arr[0] = NULL;
	data->tmp->ex_arr[1] = NULL;
	data->tmp->ex_arr[2] = NULL;
	data->tmp->ex_arr[3] = NULL;
	// ft_printf("dat i = %d\n", data->i);
	if (data->tmp->filename == NULL || data->tokens->args[data->i] == NULL)
 	{
		ft_printf("filename is NULL , we hve finsihed the pipes\n");
		return (-1);
	}
	if (data->tmp->filename != NULL)
	{
		data->tmp->ex_arr[0] = data->tmp->filename;// ft_strdup(data->tmp->filename);
		// ft_printf("set array  0 = %s\n", data->tmp->ex_arr[0]);
		x++;
		data->i++;
	}
	// ft_printf("dat i for flag = %d\n", data->i);
	if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] == '-')
	{
		// ft_printf("added flag\n");
		data->tmp->ex_arr[1] = data->tokens->args[data->i];// ft_strdup(data->tokens->args[x + 1]); // flag;
		// ft_printf("set array  0 = %s\n", data->tmp->ex_arr[1]);
		x++;
		data->i++;
		flag = 1;
	}
	else
		data->tmp->ex_arr[1] = NULL;
	if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] != '|')
	{
		data->tmp->ex_arr[1] = data->tokens->args[data->i];//ft_strdup(data->tokens->args[x + 1]); // argument;
		x++;
		data->i++;
	}
	else
		data->tmp->ex_arr[2] = NULL; // arguments;
	data->tmp->ex_arr[3] = NULL; // last one is null
	return (data->i);
}

static int update_i(t_data *data, int i)
{
	int x;
	
	x = i;
	if (data->tmp->filename == NULL)
	{
		ft_printf("filename is null we should be at the end \n");
		return(-1);
	}
	while (i > 0)
	{
		// ft_printf("_____________i = %d______________ \n", i);
		if (data->tmp->filename != NULL && data->tokens->args[x] != NULL)
			x++;
		if (data->tokens->args[x] != NULL && data->tokens->args[x][0] == '-') // why is this overflow??????
			x++;
		if (data->tokens->args[x] != NULL && data->tokens->args[x][0] != '|')
			x++;
		i--;
	}
	return (x);	
}

/// this works for 1 pipe just fine just switch back to orginal name below and uncomment
// int pipe_fork(t_data *data, int i)
int	children(t_data *data, int fds[2])
{
	
//	int fds[2];
	pid_t child[2];
	int status;
	int testies;

	testies = 0;
	// set_array(data, data->i);//(just i
	if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] == '|')
		data->i++;
	if (pipe(fds) == -1)
	{
		ft_printf("error in pipe\n");
	}
	child[0] = fork();
	if (child[0] == -1)
	{
		ft_printf("errror in first child perror\n");
	}
	if (child[0] == 0)
	{
		testies = dup2(fds[1], STDOUT_FILENO);
		close(fds[0]); // closing read end
		close(fds[1]);
		execve(data->tmp->filename, data->tmp->ex_arr, NULL);		
		ft_printf("need perror here, exceve ffailed in piep fork\n");
		exit(1);
	}
	else
	{
		waitpid(child[0], &status, 0);
		child[1] = fork();
		if (child[1] == -1)
		{
			ft_printf("error in second child need perror\n");
		}
		if (child[1] == 0)
		{
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]); // closing read end
			close(fds[1]);
			check_path(data->tmp->env_line, 1, data, data->i);
			set_array(data, data->i); //////////
			execve(data->tmp->filename, data->tmp->ex_arr, NULL);
			exit(1);
		}
		else
		{
			close(fds[0]); // closing read end
			close(fds[1]);
			close(child[0]);
			close(child[1]);

		}
	}
	waitpid(child[0], &status, 0);
	waitpid(child[1], &status, 0);
	close(fds[0]);
	close(fds[1]);
	close(child[0]);
	close(child[1]);
	return (0);
}
int pipe_fork(t_data *data, int i)
{
	int fds[data->tokens->pipe_count * 2];
	int x;

	x = 0;
	ft_printf("holding i = %d\n", i);
	while (x < data->tokens->pipe_count && x++)
	{
		if (pipe(fds + 2 * x) < 0)
		{
			ft_printf("error in pipe perror needed\n");
			exit(EXIT_FAILURE);
		}
		x++;
	}
	x = 0;
	while (x < data->tokens->pipe_count)
	{
	//	if (data->tokens->args[data->i]  != NULL && data->tokens->args[data->i][0] == '|') //data->tokens->args[data->i] != NULL && 
	//		data->i++;
		if (data->i > data->tokens->array_count)
		{
			ft_printf("we are somehow out of bounds \n");
			return (-1);
		}
		if (check_path(data->tmp->env_line, 1, data, data->i) !=  -1)
		{
			set_array(data, data->i - 1); // - 1 is confusing , hunting requred
			children(data, &fds[x * 2]);
			data->i = update_i(data, data->i - 1);//, x);  // - 1 is confusing , hunting requred
		}
		x++;
	}
	x  = 0;
	while (x < data->tokens->pipe_count)
	{
		close(fds[x]);
		x++;
	}
	return (0);
}

int	simple_fork(t_data *data)
{
	// int	ret;
	int	status;
	
	data->pid = fork();
	if (data->pid == -1)
	{
		ft_printf("fork error\n");
		exit(1);
	}
	if (data->pid == 0)
	{
		if (execve(data->tmp->filename, data->tmp->ex_arr, NULL) == -1)
		ft_printf("exceve fail\n");
	}
	waitpid(data->pid, &status, 0);
	close(data->pid);
	return (0);
}
