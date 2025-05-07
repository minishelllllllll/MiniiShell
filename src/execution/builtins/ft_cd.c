#include "../../../includes/minishell.h"

int set_env(char *var, char *new_value, t_env *envs)
{
	char *new_key; //must to be freed

	while (envs)
	{
		new_key = ft_strjoin(envs->key, "="); //join key with = to compare 
		if(ft_strncmp(var, new_key, ft_strlen(var)) == 0)
		{
			free(envs->value);
			envs->value = ft_strdup(new_value);
			return(EXIT_SUCCESS);
		}
		envs = envs->next;
	}
	return(EXIT_FAILURE); // not found 
}

int ft_cd(char *path, t_env *envs)
{
	int retrn;
	char *pwd;
	char *oldpwd;
 
	//printf("OLDPWD : %s\n", getenv("OLDPWD"));
	//printf("PWD : %s\n", getenv("PWD"));

	oldpwd = getcwd(NULL, 0); //check if failed

	retrn = chdir(path);
	if(retrn == -1) // when chdir failed
	{
		printf("%s\n",strerror(errno));
		free(oldpwd);
		return(EXIT_FAILURE);
	}

	pwd = getcwd(NULL, 0);

	if(set_env("OLDPWD=", oldpwd, envs) == 1 || set_env("PWD=", pwd, envs) == 1)
	{
		printf("%s\n",strerror(errno)); //errors in the stderror (2);
		free(oldpwd);  
		free(pwd);
		return(EXIT_FAILURE);
	}

	return(EXIT_SUCCESS);
}

//oldpwd and pwd..
