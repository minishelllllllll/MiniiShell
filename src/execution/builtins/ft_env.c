#include "../../../includes/minishell.h"


int ft_env(t_env *envs)
{

	while (envs)
	{
		if(envs->flag_exported == 1)
		{	
			printf("%s", envs->key);
			printf("=");
			printf("%s\n", envs->value);
		}
		envs = envs->next;
	}

	return(EXIT_SUCCESS);
}