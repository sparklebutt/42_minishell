/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:52 by araveala          #+#    #+#             */
/*   Updated: 2024/08/15 12:10:48 by araveala         ###   ########.fr       */
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
		/*if (flag == 2)
		{
				dprintf(2, "pipes handeling redir\n");
		}*/
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
	int i = 0;
	printf("FOLLOWING OUR TOKENS 1 data i = %d = %s\n", data->i, data->tokens->args[data->i]);
	if (is_builtins(data->tokens->args[data->i]) == 1) {
		printf("FOLLOWING OUR TOKENS 2 data i = %d = %s\n", data->i, data->tokens->args[data->i]);		
		child(data, fds, prev_fd, x, 1);
		data->i++;
		printf("FOLLOWING OUR TOKENS 3 data i = %d = %s\n", data->i, data->tokens->args[data->i]);	
		while (data->tokens->args[data->i] != NULL)
		{
			printf("FOLLOWING OUR TOKENS 4 data i = %d = %s\n", data->i, data->tokens->args[data->i]);	
			if (data->tokens->args[data->i][0] == '|')
			{
				data->i++;
				printf("FOLLOWING OUR TOKENS 5 data i = %d = %s\n", data->i, data->tokens->args[data->i]);	
				break ;
			}
			printf("FOLLOWING OUR TOKENS 6 data i = %d = %s\n", data->i, data->tokens->args[data->i]);		
			data->i++;
		}
		printf("FOLLOWING OUR TOKENS 7 data i = %d = %s\n", data->i, data->tokens->args[data->i]);	
	}	
	else if (is_redirect(data->tokens->args[data->i])) // || is_redirect(data->tokens->args[data->i + 1]))
	{
		printf("FOLLOWING OUR TOKENS 8 data i = %d = %s\n", data->i, data->tokens->args[data->i]);	
		set_env_array(data);
	//	printf("exx arr 0 = %s\n", data->tmp->ex_arr[0]);
	//	printf("exx arr 1 = %s\n", data->tmp->ex_arr[1]);	
	//	printf("exx arr 2 = %s\n", data->tmp->ex_arr[2]);
	//	printf("exx arr 3 = %s\n", data->tmp->ex_arr[3]);
		// check array , only want cat so if no input output file?
		// only cat else ?
		if (simple_fork(data) == 0)
			printf("\n");
	}
	else if (check_path(data->tmp->env_line, 1, data, data->i) != -1)
	{
		printf("FOLLOWING OUR TOKENS 9 data i = %d = %s\n", data->i, data->tokens->args[data->i]);	
		if (data->tokens->args[data->i + 1][0] == '>')
		{
				printf("1~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ data i = %d\n", data->i);
				//printf("whats in env line = %s\n", data->tmp->env_line );
				while (data->tokens->args[data->i] != NULL)
				{
					printf("loop count = %d and a char = %s\n", i, data->tokens->args[data->i]);
					i++;
					data->i++;
					printf("loop count = %d and a char = %s\n", i, data->tokens->args[data->i]);
					if (ft_strncmp(data->tokens->args[data->i], "|", 1) == 0)
					{
						i++;
						data->i++;	
						if (check_path(data->tmp->env_line, 1, data, data->i) != -1)
						{
							printf("2~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
							i += set_array(data);
							//break ; // ?
							simple_fork(data);
							printf("3~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
							break ;
						}
				//		simple_fork(data);		
					}
				}
		}
		if (i > 0)
		{
			data->i -= i;
			x++;
		}
		printf("4~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~data i should have returned = %d\n",  data->i);	
//		printf("we want a redir sending to chil here = %s\n", data->tokens->args[data->i]);
		printf("\tjust setting array\n");
		set_array(data); // needs to take into consideration some factors, vilja fix?

		//printf("exx arr 0 = %s\n", data->tmp->ex_arr[0]);
		//printf("exx arr 1 = %s\n", data->tmp->ex_arr[1]);	
		//printf("exx arr 2 = %s\n", data->tmp->ex_arr[2]);
		//printf("exx arr 3 = %s\n", data->tmp->ex_arr[3]);
		child(data, fds, prev_fd, x, 0);
		printf("\tchild has been executed\n"); // this runs a last round empty for some reason, wont fix it yet , it might be usefull
		printf("FOLLOWING OUR TOKENS 10 data i = %d = %s\n", data->i, data->tokens->args[data->i]);
		if (data->tokens->args[data->i] != NULL && data->tokens->args[data->i][0] == '|')
			data->i++;
		printf("FOLLOWING OUR TOKENS 11 data i = %d = %s\n", data->i, data->tokens->args[data->i]);
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
	close(fds[1]);
	if (prev_fd != -1)
		close(prev_fd);
	return (0);
}

int	simple_fork(t_data *data)
{
	int	status;

	status = 0;
	data->pid = fork();
	if (data->pid == -1)
	{
		ft_printf("fork error\n"); // change error message
		exit(1);
	}
	else if (data->pid == 0)
	{	
		if (data->tokens->redirect_count >= 1) // this needs an order od operation
		{
			printf("let me know\n");
			// printf("REDIRECTS EXIST\n");
			printf("exx arr 0 = %s\n", data->tmp->ex_arr[0]);		
			printf("exx arr 1 = %s\n", data->tmp->ex_arr[1]);	
			printf("exx arr 2 = %s\n", data->tmp->ex_arr[2]);
			printf("exx arr 3 = %s\n", data->tmp->ex_arr[3]);
			apply_redirections(data->tokens);
			// exit(1);
		}
//		printf("");
		if (execve(data->tmp->filename, data->tmp->ex_arr, data->env_array) == -1)
			ft_printf("exceve fail\n");
		exit(1); // should this be different kind of error handelin
	}
	waitpid(data->pid, &status, 0);
//	list_open_fds();
	return (0);
}
