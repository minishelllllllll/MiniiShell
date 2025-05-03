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
	char *avv[3] = {"execut", "Abc", NULL};

	envs = list_envs(envp);

	//ft_env(envs);
	//if(ft_strncmp(av[1], "exit", 4) == 0)
		//ft_exit(av);
			
	//ft_env(envs);
	//ft_env(envs);
	//printf("\n\n\n\n");
	
	ft_export(av, envs);
	ft_env(envs);

	printf("\n\n\n\n");

	ft_unset(avv, &envs);
	ft_env(envs);
	

	free_list(&envs);
//	ft_cd(av[1], envs);
	//ft_env(envs);
	//list_envs();

}