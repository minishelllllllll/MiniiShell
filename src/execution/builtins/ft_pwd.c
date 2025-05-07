#include "../../../includes/minishell.h"

//no leak 

int ft_pwd()
{
	char *working_d;

	working_d = getcwd(NULL, 0);
	if(!working_d)
	{
		printf("%s\n", strerror(errno));
		return(EXIT_FAILURE);
	}
	printf("%s\n", working_d);
	free(working_d);
	return(EXIT_SUCCESS);
}
