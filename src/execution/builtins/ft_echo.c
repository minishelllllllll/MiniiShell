#include "../../../includes/minishell.h"


int echo(char **args)
{
	int i;
	int check;

	i = 1;
	check = 0;
	if(ft_strncmp(args[i], "-n", 3) == 0) // check the first arg is -n\0?
	{
		i++;
		check = 1;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if(args[i + 1])
			printf(" ");
		i++;
	}
	if(check == 0)
		printf("\n");

	return(EXIT_SUCCESS);
}

