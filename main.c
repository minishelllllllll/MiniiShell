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

void print_2d_array(char **arr)
{
	int i = 0;

	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	int status;
	char *rdl;
	char **command;
	char *exec_path;
	char *cwd;
	char *prompt;

	t_env *envs;

	char **env_arr;

	envs = list_envs(envp);

	while (1)
	{
		cwd = getcwd(NULL, 0);
		if(!cwd)
			cwd = get_env_value("PWD", envs);//getcwd(NULL, 0);

		prompt = ft_strjoin(cwd, " $> ");
		rdl = readline(prompt);

		command = ft_split(rdl, 32);
		
		if(ft_builtin(command, &envs) == -1)
		{
			if(fork() == 0)
			{
				exec_path = executable_path(command[0], envs);
				env_arr = envs_to_array(envs);
				print_2d_array(env_arr);
				if(execve(exec_path, command, env_arr) == -1)
				{
					printf("minishell: command not found: %s\n", command[0]);
					exit(EXIT_FAILURE);
				}
			}
			else
				wait(&status);
		}
	}
	return (0);
}