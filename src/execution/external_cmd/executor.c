#include "../../../includes/minishell.h"


int	len_list_cmd(t_cmd *temp)
{
	int i;

	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return(i);
}

void ft_execve(t_env *envs, t_cmd *tmp_cmd)
{
	char *exec_path;
	char **env_arr;

	exec_path = executable_path(tmp_cmd->full_cmd[0], envs);
	env_arr = envs_to_array(envs);
	if(execve(exec_path, tmp_cmd->full_cmd, env_arr) == -1)
	{
		printf("minishell: command not found: %s\n", tmp_cmd->full_cmd[0]);
		exit(EXIT_FAILURE);
	}
}

void  execute_commands(t_env **envs, t_cmd *tmp_cmd)
{
	int **pipes;
	
	int (i), (len_cmd);
	// count len of linked list (how many command)
	len_cmd = len_list_cmd(tmp_cmd);
	// allocate 2d array of pipes
	pipes = piping(len_cmd - 1);
	i = 0;
	while (i < len_cmd)
	{
		if(len_cmd == 1) // if one command
		{
			duplication(i, len_cmd, pipes, tmp_cmd);
			if(ft_builtin(tmp_cmd->full_cmd, envs) == -1) // is a builtin don't fork , execute it in parent.
			{
				if(fork() == 0)
				{
					close_pipes(len_cmd - 1, pipes);
					ft_execve((*envs), tmp_cmd);
				}
			}
		}
		else if(fork() == 0)
		{
			// diplucate stdout with pipe[1] if we are in the first command(i, len_cmd, pipes)
			duplication(i, len_cmd, pipes, tmp_cmd);
			// execute the commands
			if (ft_builtin(tmp_cmd->full_cmd, envs) == 0)
			{
				close_pipes(len_cmd - 1, pipes); // important!
				exit(0); // child must exit after finishing the builtin
			}
			else
				ft_execve((*envs), tmp_cmd);
		}
		tmp_cmd = tmp_cmd->next;
		i++;
	}
	close_pipes(len_cmd - 1, pipes);
}


void duplication(int i, int len_cmd, int **pipes, t_cmd  *tmp_cmd)
{
	if(i == 0) // first command
	{
		if(tmp_cmd->in_file != -1) // duplicate stdin with pipes or redirection,
		{
			if (dup2(tmp_cmd->in_file, STDIN_FILENO) == -1)
				perror("dup2 in_file"); // errorrr handliingggg 
			close(tmp_cmd->in_file);
		}
		if(tmp_cmd->out_file != -1)
		{
			dup2(tmp_cmd->out_file, STDOUT_FILENO);
			close(tmp_cmd->out_file);
		}
		else if(len_cmd > 1)
			dup2(pipes[i][1], STDOUT_FILENO); // diplucate the stdout to write in pipe
		close_pipes(len_cmd - 1, pipes);
	}
	else if (i < len_cmd - 1) // middle command [ .... |   | .... ]
	{
		if(tmp_cmd->in_file != -1) 
		{
			dup2(tmp_cmd->in_file, STDIN_FILENO);
			close(tmp_cmd->in_file);
		}
		else
			dup2(pipes[i - 1][0], STDIN_FILENO);

		if(tmp_cmd->out_file != -1)
		{
			dup2(tmp_cmd->out_file, STDOUT_FILENO);
			close(tmp_cmd->out_file);
		}
		else
			dup2(pipes[i][1], STDOUT_FILENO);
		close_pipes(len_cmd - 1, pipes);
	}
	else if (i == len_cmd - 1)  // last command 
	{
		if(tmp_cmd->in_file != -1) 
		{
			dup2(tmp_cmd->in_file, STDIN_FILENO);
			close(tmp_cmd->in_file);
		}
		else
			dup2(pipes[i - 1][0], STDIN_FILENO); // diplucate the stdin to read from pipe

		if(tmp_cmd->out_file != -1)
		{
			dup2(tmp_cmd->out_file, STDOUT_FILENO);
			close(tmp_cmd->out_file);
		}

		close_pipes(len_cmd - 1, pipes);
	}
}
