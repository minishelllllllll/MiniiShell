#include "../../../includes/minishell.h"


int ft_export(char **args, t_env *envs)
{
	int i;
	t_env *newnode;

	i = 1;
	while (args[i])
	{
		newnode = new_env(args[i]);
		add_env(newnode, &envs);
		i++;
	}

	return(EXIT_SUCCESS);
}