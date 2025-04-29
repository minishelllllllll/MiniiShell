#include "../../../includes/minishell.h"


// i think is done *_*

int ft_env(char **args)
{
	(void)args;
	int i;

	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	

	return(EXIT_SUCCESS);
}