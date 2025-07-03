/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:47:30 by nahilal           #+#    #+#             */
/*   Updated: 2025/06/12 18:03:28 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <readline/history.h>

int	G_EXIT_STATUS = 0;
g_exit_status
int	skip_space_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int *saved_stdin_out(t_env *envs)
{
	int *in_out;

	in_out = (int *)g_collector(sizeof(int) * 2, envs);

	in_out[0] = dup(STDIN_FILENO);
	in_out[1] = dup(STDOUT_FILENO);
	if(in_out[0] == -1 || in_out[1] == -1)
		perror("minishell");
	return(in_out);
}

void restore_stdin_out(int *saved_in_out)
{
	if(dup2(saved_in_out[0], STDIN_FILENO) == -1)
		perror("dup2 ");
	if(dup2(saved_in_out[1], STDOUT_FILENO) == -1)
		perror("dup2 ");
	close(saved_in_out[0]);
	close(saved_in_out[1]);
}

char *shell_prompt(t_env *envs)
{
	char *cwd;
	char *prompt;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		prompt = ft_strjoin(cwd, " $> ", envs);
		free(cwd);    /////////////////////////////// addeeed to execution branch
		return(prompt);
	}
	cwd = get_env_value("PWD", envs);
	if(!cwd) // in case no pwd and fail getcwd
	{
		cwd = ft_strdup("..", envs);
		prompt = ft_strjoin(cwd, " $> ", envs);
		return(prompt);
	}
	prompt = ft_strjoin(cwd, " $> ", envs);
	return(prompt);
}
int lexer_checker(char *rdl, t_env *envs, t_cmd **cmd)
{
	t_parsing   *head;

	head = lexer(rdl, envs);
	if(checker(head,envs,ft_strlen(rdl),cmd) == 2)
	{
		free(rdl);
		return(0);
	}
	return(1);
}
int space_skip_main(char *rdl)
{
	int len;

	if(skip_space_str(rdl) == 1)
	{
		len = ft_strlen(rdl);
		add_history(rdl);
	}
	else
	{
		len = 0;
		free(rdl);
		return(0);
	}
	return(len);
}
char *read_line(t_env *envs, char *rdl)
{

	rdl = readline(shell_prompt(envs));
	if (!rdl)
	{
		printf("exit\n");
		clean_memory(&(envs->head_gc));
		free_list(&envs);
		exit(G_EXIT_STATUS);
	}
	return(rdl);
}
int *save_in_out(t_env *envs)
{
	int     *arr_in_out;

	arr_in_out = saved_stdin_out(envs);
	if(arr_in_out[0] == -1 || arr_in_out[1] == -1)
	{
		free_list(&envs);
		exit(G_EXIT_STATUS);
	}
	return(arr_in_out);
}

int send_to_execution(t_cmd *cmd, t_env *envs, int *arr_in_out,char *rdl)
{
	t_cmd   *commads_in_out;
	t_pids  *pids;

	commads_in_out = cmd;
	if (commads_in_out)
	{
		pids = execute_commands(&envs, commads_in_out);
		if (!pids)
			return (0);       
		restore_stdin_out(arr_in_out);
		waiting_childs(pids);

	}
	free(rdl);
	cmd = NULL;
	clean_memory(&(envs->head_gc));
	return (1);
}
int main_loop(t_env *envs)
{
	int     *arr_in_out;
	char    *rdl;
	t_cmd   *cmd;

	cmd = NULL;
	rdl = NULL;
	arr_in_out = save_in_out(envs);
	rdl = read_line(envs , rdl);
	if(space_skip_main(rdl) == 0)
		return(1);
	if(lexer_checker(rdl,envs,&cmd) == 0)
		return(1);
	if(send_to_execution(cmd, envs, arr_in_out,rdl) == 0)
		return(0);
	return (2);
}
int main(int ac, char **av, char **envp)
{
	t_env   *envs;
	int i;

	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	envs = list_envs(envp);
	if(!envs)
	{
		ft_putstr_fd("minishell: error initializing environment\n", 2);
		free_list(&envs);
		return (1);
	}
	envs->head_gc = NULL;
	while (1)
	{
		signal(SIGINT, my_handller);
		i = main_loop(envs);
		if(i == 1)
			continue;
		if(i == 0)
			return(0);
	}
	return (0);
}
