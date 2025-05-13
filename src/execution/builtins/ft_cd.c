#include "../../../includes/minishell.h"

int set_env(char *var, char *new_value, t_env *envs)
{
	while (envs)
	{
		if(ft_strcmp(var, envs->key) == 0)
		{
			free(envs->value);
			envs->value = ft_strdup(new_value);
			return(0);
		}
		envs = envs->next;
	}
	return(1); // not found 
}

char *get_env_value(char *key, t_env *envs)
{
    while (envs)
    {
        if (ft_strcmp(key, envs->key) == 0)
            return (envs->value);
        envs = envs->next;
    }
    return NULL; // not found
}

int ft_cd(char **args, t_env *envs)
{
	char *pwd;
	char *oldpwd;
	int i;

	i = 0;
	while (args[i] != NULL)
		i++;
	if(i > 2)
	{
		printf("cd: too many arguments\n");
		return(EXIT_FAILURE); // exit status == 1
	}
	
	oldpwd = get_env_value("PWD", envs);//getcwd(NULL, 0); //check if failed
	if(oldpwd == NULL) // when getcwd failed
		return(EXIT_FAILURE);

	if(args[1] == NULL || ft_strcmp(args[1], "~") == 0)
	{
		if(chdir(get_env_value("HOME", envs)) == -1)
		{
			printf("cd: HOME not set");
			return(EXIT_FAILURE);	
		}
	}
	else if(chdir(args[1]) == -1) // when chdir failed
	{
		printf("%s\n",strerror(errno));
		return(EXIT_FAILURE);
	}

	pwd = getcwd(NULL, 0);
	if(pwd == NULL) // when getcwd failed
	{
		printf("%s\n",strerror(errno));
		return(EXIT_FAILURE);
	}

	if(set_env("OLDPWD", oldpwd, envs) == 1 || set_env("PWD", pwd, envs) == 1)
		return(EXIT_FAILURE);

	return(EXIT_SUCCESS);
}

