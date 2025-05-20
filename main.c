/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:47:30 by nahilal           #+#    #+#             */
/*   Updated: 2025/04/21 20:06:43 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_cmd *create_cmd_list(char *rdl)
{
    char **commands;
    t_cmd *head_cmd = NULL;  // Head of the list
    t_cmd *current = NULL;   // Current node for building the list
    t_cmd *new_cmd;
    int i = 0;
    commands = ft_split(rdl, '|');
    while (commands[i])
    {
        new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
        new_cmd->full_cmd = ft_split(commands[i], 32); // 32 is ASCII for space
        new_cmd->next = NULL;
        if (!head_cmd)
        {
            head_cmd = new_cmd;
            current = new_cmd;
        }
        else
        {
            current->next = new_cmd;
            current = new_cmd;
        }
        i++;
    }
    return (head_cmd);
}

void print_commands(t_cmd *cmd_list)
{
    t_cmd *current;
    int cmd_num = 0;
    int i;
    current = cmd_list;
    while (current)
    {
        printf("Command %d: ", cmd_num++);
        
        if (current->full_cmd)
        {
            i = 0;
            while (current->full_cmd[i])
            {
                printf("%s ", current->full_cmd[i]);
                i++;
            }
        }
        else
            printf("(empty)");
        printf("\n");
        current = current->next;
    }
}

void print_2d_array(int **arr)
{
	int i = 0;

	while (arr[i])
	{
		printf("%d\n", arr[i][0]);
		printf("%d\n", arr[i][1]);
		i++;
	}
}

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

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char *rdl;
	char *cwd;
	char *prompt;

	int len_cmd;
	t_env *envs;
	t_cmd  *commads_in_out;
	t_cmd  *tmp_cmd;

	int **pipes;
	int i;

	envs = list_envs(envp);
	while (1)
	{
		// prompt
		cwd = getcwd(NULL, 0);
		if(!cwd)
			cwd = get_env_value("PWD", envs);
		prompt = ft_strjoin(cwd, " $> ");
		rdl = readline(prompt);

		// parssing command by pipe and space
		commads_in_out = create_cmd_list(rdl);
		tmp_cmd = commads_in_out;

		// count len of linked list (how many command)
		len_cmd = len_list_cmd(tmp_cmd);
			//printf("we have %d command\n", len_cmd);
		
		// allocate 2d array of pipes
		pipes = piping(len_cmd - 1);

		i = 0;
		// loop to execute the commands in childs processes
		while (i < len_cmd) 
		{
			if(len_cmd == 1) // if one command
			{
				if(ft_builtin(tmp_cmd->full_cmd, &envs) == -1) // is a builtin dont fork , execute it in parent.
				{
					if(fork() == 0)
					{
						close_pipes(len_cmd - 1, pipes);
						execute_commands(envs, tmp_cmd);
					}
				}
			}
			else if(fork() == 0)
			{
				// diplucate stdout with pipe[1] if we are in the first command(i, len_cmd, pipes)
				duplication(i, len_cmd, pipes, tmp_cmd);
				// execute the commands
				if(ft_builtin(tmp_cmd->full_cmd, &envs) == 0)
					return(0);
				else
					execute_commands(envs, tmp_cmd);
			}
			tmp_cmd = tmp_cmd->next;
			i++;
		}
		close_pipes(len_cmd - 1, pipes);
		waiting_childs(len_list_cmd(commads_in_out));
	}
	return (0);
}


/*
handell redirections

( echo "$USER $PATH" > file | grep usr << limiter | wc -l < file >> out_file )
[ < file wc -l < file > out_file ]


handlle appande
handel heredoc

waitpid
exit status
signals 

*/


// dprintf(STDERR_FILENO ,"pipesss[%d][0] = %d\n", i - 1, pipes[i - 1][0]);
