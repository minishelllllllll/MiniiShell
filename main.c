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
		
		new_cmd->in_file = -1;
        new_cmd->out_file = -1;
        
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

t_cmd *process_redirections(t_cmd *cmd_list)
{
    t_cmd *current = cmd_list;
    
    while (current)
    {
        int i = 0;
        while (current->full_cmd && current->full_cmd[i])
        {
            if (i + 1 < count_args(current->full_cmd))
            {
                // Input redirection
                if (strcmp(current->full_cmd[i], "<") == 0)
                {
                    if (current->in_file != -1)
                        close(current->in_file);
                    current->in_file = open(current->full_cmd[i + 1], O_RDONLY);
                    remove_args(current->full_cmd, i, 2);
                    continue;
                }
                // Heredoc
                else if (strcmp(current->full_cmd[i], "<<") == 0)
                {
                    if (current->in_file != -1)
                        close(current->in_file);
                    current->in_file = heredoce(current->full_cmd[i + 1]);
                    remove_args(current->full_cmd, i, 2);
                    continue;
                }
                // Output redirection (overwrite)
                else if (strcmp(current->full_cmd[i], ">") == 0)
                {
                    if (current->out_file != -1)
                        close(current->out_file);
                    current->out_file = open(current->full_cmd[i + 1], 
                                            O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    remove_args(current->full_cmd, i, 2);
                    continue;
                }
                // Output redirection (append)
                else if (strcmp(current->full_cmd[i], ">>") == 0)
                {
                    if (current->out_file != -1)
                        close(current->out_file);
                    current->out_file = open(current->full_cmd[i + 1], 
                                            O_WRONLY | O_CREAT | O_APPEND, 0644);
                    remove_args(current->full_cmd, i, 2);
                    continue;
                }
            }
            i++;
        }
        current = current->next;
    }
    
    return cmd_list;
}

t_cmd *process_heredocs(t_cmd *cmd_list)
{
    t_cmd *current = cmd_list;
    
    while (current)
    {
        int i = 0;
        while (current->full_cmd && current->full_cmd[i])
        {
            // Check for heredoc
            if (current->full_cmd[i] && i + 1 < count_args(current->full_cmd) && 
                strcmp(current->full_cmd[i], "<<") == 0 && current->full_cmd[i + 1])
            {
                // Set up heredoc
                int heredoc_fd = heredoce(current->full_cmd[i + 1]);
                if (heredoc_fd == -1)
                    return NULL; // Error handling
                
                // If there's already an input redirection, close it
                if (current->in_file != -1)
                    close(current->in_file);
                
                current->in_file = heredoc_fd;
                
                // Remove "<<" and delimiter from arguments
                remove_args(current->full_cmd, i, 2);
                
                // Don't increment i as we've removed elements
                continue;
            }
            i++;
        }
        current = current->next;
    }
    
    return cmd_list;
}

// Helper function to count arguments
int count_args(char **args)
{
    int count = 0;
    while (args[count])
        count++;
    return count;
}

// Helper function to remove elements from argument array
void remove_args(char **args, int start, int count)
{
    int i = start;
    int total = count_args(args);
    
    // Free the strings we're removing
    for (int j = 0; j < count; j++)
        if (args[start + j])
            free(args[start + j]);
    
    // Shift remaining arguments
    while (start + count + (i - start) < total)
    {
        args[i] = args[start + count + (i - start)];
        i++;
    }
    
    // Null-terminate
    args[i] = NULL;
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


	int saved_stdin;
	int saved_stdout;

	envs = list_envs(envp);

	while (1)
	{

		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);

		// prompt
		cwd = getcwd(NULL, 0);
		if(!cwd)
			cwd = get_env_value("PWD", envs);
		prompt = ft_strjoin(cwd, " $> ");
		
		
		rdl = readline(prompt);
		//printf("%s\n", rdl);
    
		if (!rdl) // Handle Ctrl+D (EOF)
		{
			printf("exit\n");
			break;
		}

		// parssing command by pipe and space
		commads_in_out = create_cmd_list(rdl);
		commads_in_out = process_redirections(commads_in_out);

		tmp_cmd = commads_in_out;
		//printf("infile %d \n", tmp_cmd->in_file);


		// count len of linked list (how many command)
		len_cmd = len_list_cmd(tmp_cmd);
		//printf("len %d \n", len_cmd);

		// allocate 2d array of pipes
		pipes = piping(len_cmd - 1);

		i = 0;
		// loop to execute the commands in childs processes
		while (i < len_cmd) 
		{
			if(len_cmd == 1) // if one command
			{
				duplication(i, len_cmd, pipes, tmp_cmd);
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
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		close_pipes(len_cmd - 1, pipes);
		waiting_childs(len_list_cmd(commads_in_out));
	}
	return (0);
}


/*
handell redirections

( echo "$USER $PATH" > file | grep usr << limiter | wc -l < file >> out_file )
[ < file wc -l < file > out_file ]

handel heredoc ~solved~

split functions ~

handle waitpid ~

error handling, in all functions  ~ 

handle exit status ~

handle signals ~

garbeg collectore ~

*/


// dprintf(STDERR_FILENO ,"pipesss[%d][0] = %d\n", i - 1, pipes[i - 1][0]);
