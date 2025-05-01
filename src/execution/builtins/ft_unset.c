#include "../../../includes/minishell.h"

void	update_env(int i)
{

	while (environ[i])
	{
		//printf("that ==> %s\n", environ[i]);
		//printf("with that ==> %s\n\n", environ[i + 1]);
		environ[i] = environ[i + 1];
		i++;
	}
}

int ft_unset(char **env)
{
	int i;
	int j;
	
	i = 1; //1 name of program
	while (env[i])
	{
		j = 0;
		while (environ[j])
		{
			if(ft_strncmp(env[i], environ[j], ft_strlen(env[i])) == 0)
			{
				update_env(j);
				break;
			}
			j++;
		}
		i++;
	}
	return(EXIT_SUCCESS);
}

//nothing happen when we dont found that variable

// rm many envs ............. ~~~~
// "unset A not_exist Abc" ==> rm A and Abc ~~~~
// unset with failure ???


// typedef struct s_env
// {
//     char *key;           // Variable name
//     char *value;         // Variable value
//     struct s_env *next;  // Next node
// } t_env;

