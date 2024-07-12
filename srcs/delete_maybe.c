/*		ft_printf("0 = %s", data->tmp->ex_arr[0]);
		ft_printf("0 = %s", data->tmp->ex_arr[1]);
		ft_printf("0 = %s", data->tmp->ex_arr[2]);
		ft_printf("0 = %s\n", data->tmp->ex_arr[3]);
*/
/*static int child(t_data *data, int *fds, int x) // only fds
{
	int z;
	int status;
	pid_t child;
	z = 0;
	if (x < data->tokens->pipe_count)// && update_(data))// && x++)
	{
		ft_printf("ENTERED pipe\n");
		child = fork();
		if (child == -1)
			ft_printf("errror in first child\n");
		if (child == 0)
		{
			ft_printf("ENTERED child\n");
			if (x > 0)
				dup2(fds[2 * (x - 1)], STDOUT_FILENO);
//				dup2(fds[0], STDOUT_FILENO);
			if ( x < data->tokens->pipe_count - 1)
				dup2(fds[2 * (x + 1)], STDIN_FILENO);
//				dup2(fds[1], STDIN_FILENO);
			while (z < 2 * x)//data->tokens->pipe_count)// && z++)
			{
				close(fds[0]);//(fds[z]); //clsoing read end
//			close(fds[1]); //clsoing read end
				z++;
			}
//			if (data->tokens->args[data->i][0] == '|')
//				data->i += 1;
//			check_path(data->tmp->env_line, 1, data, data->i);
//			data->i = update_i(data, data->i, x);
//			set_array(data, data->i);
			execve(data->tmp->filename, data->tmp->ex_arr, NULL);
			dprintf(2, "exceve  fail bu8t with dprintf\n");
			exit(1);
		}
		else
		{
			ft_printf("parent here\n");
//			x++;
		}
//		x++;
//		check_path(data->tmp->env_line, 1, data, data->i);
		data->i = update_i(data, data->i, x);
//		set_array(data, data->i);

	}
//	update_i(data, data->i);
//	x = 0;
	while (x < 2 * data->tokens->pipe_count && x++)
		close(fds[x]);
	while (waitpid(child, &status, 0) > 0)
		dprintf(2, "waiting but with dprintf\n");
	return(data->i);
}*/

/*int pipe_fork(t_data *data, int i)
{	
	int fds[data->tokens->pipe_count * 2]; // nnum of commands - 1 // not arguments
	pid_t child; //[2]; // might need a solid number here
	int status;
	int x;
	int z;
	int test;
	x = 0; //set up stuuff
	z = 0;
	test = 0;
	if (i == 10)
		ft_printf("i = %d", i);
	while (x < data->tokens->pipe_count && x++)
	{
		if (pipe(fds + 2 * x) < 0)//
		{
			ft_printf("error in pipe\n");
			exit(EXIT_FAILURE);
		}
	}
	x = 0;
//	set_array(data, i);//(data, data->i);
	ft_printf("lets see starting point x = %d && pipe_count = %d\n", x, data->tokens->pipe_count);
	while (x < data->tokens->pipe_count) //&& set_array(data, data->i) == 1)// && update_(data))// && x++)
	{

		if (x > 0)
			data->i = update_i(data, x, data->i);			
		set_array(data, data->i);
		dprintf(2, "ENTERED = %x loop\n", x);


//		check_path(data->tmp->env_line, 1, data, data->i);
//		set_array(data, data->i);
//		test = child(data, fds, x);
//		ft_printf("test = %d\n");

		child = fork();
		if (child == -1)
			ft_printf("errror in first child\n");
		if (child == 0)
		{
			ft_printf("\n\nWHAT IS X = ======= %d\n\n", x);
			if (x > 0)
				dup2(fds[2 * (x - 1)], STDOUT_FILENO); //
			if ( x < data->tokens->pipe_count - 1)
				dup2(fds[2 * (x + 1)], STDIN_FILENO);
			while (z < 2 * data->tokens->pipe_count && z++)
			{
				close(fds[z]); //clsoing read end
//				z++;
			}
			if (data->tokens->args[data->i][0] == '|')
				data->i += 1;
//			data->i = update_i(data, data->i, x);
			check_path(data->tmp->env_line, 1, data, data->i);

			set_array(data, data->i);
			execve(data->tmp->filename, data->tmp->ex_arr, NULL);
			dprintf(2, "exceve  fail bu8t with dprintf\n");
			exit(1);
		}
		x++;
//		check_path(data->tmp->env_line, 1, data, data->i);
//		data->i = update_i(data, data->i, x);
//		set_array(data, data->i);
//		x++;
	}
	x = 0;
	update_i(data, x, data->i); //holdig
	while (x < 2 * data->tokens->pipe_count && x++)
		close(fds[x]);
	while (waitpid(child, &status, 0) > 0)
		dprintf(2, "waiting but with dprintf\n");
	return (0);
	}*/


/*		else

		//sep func
		data->tmp->ex_arr[0] = NULL;
		data->tmp->ex_arr[1] = NULL;
		data->tmp->ex_arr[2] = NULL;
		data->tmp->ex_arr[3] = NULL;
//		free_array_2(data->tmp->ex_arr, 4);

		{
			ft_printf("parent process\n");
//			close(fds[1]); // closing write end
			waitpid(child[0], &status, 0);
			child[1] = fork();
			if (child[1] == -1)
			{
				ft_printf("errror in second child\n");
			}
			if (child[1] == 0)
			{
				ft_printf("seond child is born\n");
				check_path(data->tmp->env_line, 1, data, data->i);
				set_array(data, data->i);
				execve(data->tmp->filename, data->tmp->ex_arr, NULL);
				exit(1);
			}
			else
			{
				ft_printf("parent in child\n");
//				close(fds[0]); //closing read end agian
				close(fds[0]); //clsoing read end
				close(fds[1]);
				close(child[0]);
				close(child[1]);
			}
		}
	}
	waitpid(child[0], &status, 0); //wait for second child
	waitpid(child[1], &status, 0); //wait for second child

	close(fds[0]); //clsoing read end
	close(fds[1]);
	close(child[0]);
	close(child[1]);

	return (0);
	
	}*/
