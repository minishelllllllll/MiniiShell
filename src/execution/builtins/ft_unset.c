#include "../../../includes/minishell.h"

int ft_unset(char **args, t_env *envs)
{
	t_env *temp;
	t_env *prev;
	int i;
	
	i = 1; //1 name of program
	while (args[i])
	{
		temp = envs;
		while (temp->next)
		{
			prev = temp;
			temp = temp->next;
			if(ft_strncmp(args[i], temp->key, ft_strlen(args[i])) == 0)
			{
				prev->next = temp->next;
				free(temp->key);
				free(temp->value);
				free(temp);
				break;
			}
		}
		i++;
	}
	return(EXIT_SUCCESS);
}

//nothing happen when we dont found that variable

// rm many envs ............. ~~~~
// "unset A not_exist Abc" ==> rm A and Abc ~~~~
// unset with failure ???

// Invalid variable names:
// If a variable name starts with a digit
// If a variable name contains invalid characters (only alphanumeric characters and underscore are allowed)
// If a variable name starts with a special character (other than underscore)

//Some environment variables in a shell might be marked as read-only

//Permission issues:
//In some contexts, certain variables might be protected by permission settings

//╰─$ unset
//unset: not enough arguments

//incorrect option flage 

//The **is_valid_varname** function would check if the variable name follows the required pattern 
//(starts with a letter or underscore, followed by letters, digits, or underscores).