#include "../../../includes/minishell.h"

//no leak 

int ft_pwd()
{
	char *working_d;

	working_d = get_env_value("PWD", envs);
	if(!working_d)
	{
		printf("%s\n", strerror(errno));
		return(EXIT_FAILURE);
	}
	printf("%s\n", working_d);
	return(EXIT_SUCCESS);
}
