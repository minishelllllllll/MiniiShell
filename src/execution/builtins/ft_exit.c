#include "../../../includes/minishell.h"

int ft_exit(char **args)
{
	(void)args;
	printf("exit\n");
	exit(EXIT_SUCCESS);
}