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

int main(int ac, char **av, char **envp)
{

	(void)ac;
	(void)av;
	t_env *envs;

	envs = list_envs(envp);

	//ft_env(envs);
	//if(ft_strncmp(av[1], "exit", 4) == 0)
		//ft_exit(av);
			

	/*ft_unset(av);
	printf("\nsearch for that env\n");
	char *var = getenv("B");
	if(!var)
		printf("unset B\n");
	else
		printf("found B : %s\n", var);


	var = getenv("A");
	if(!var)
		printf("unset A\n");
	else
		printf("found A : %s\n", var);


	var = getenv("Abc");
	if(!var)
		printf("unset Abc\n");
	else
		printf("found Abc : %s\n", var);*/


	ft_env(envs);
	ft_cd(av[1], envs);
	ft_env(envs);
	//list_envs();

}