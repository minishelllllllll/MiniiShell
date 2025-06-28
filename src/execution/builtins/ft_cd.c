#include "../../../includes/minishell.h"

int set_env(char *var, char *new_value, t_env *envs)
{
	while (envs)
	{
		if(ft_strcmp(var, envs->key) == 0 && new_value)
		{
			if(envs->value) // maybe no need when use gc
				free(envs->value);
			envs->value = ft_strdup(new_value);
			envs->flag_exported = 1;
			return(0);
		}
		envs = envs->next;
	}
	return(1); // not found 
}

char *get_env_value(char *key, t_env *envs)
{
	if(!key || !envs)
		return (NULL);
    while (envs)
    {
        if (ft_strcmp(key, envs->key) == 0)
            return (envs->value);
        envs = envs->next;
    }
    return NULL; // not found
}

int	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	return(EXIT_FAILURE); // exit status == 1
}

int	go_new_dir(char *new_dir)
{
	if(new_dir == NULL || ft_strcmp(new_dir, "~") == 0) // go to HOME.
	{
		if(chdir(get_env_value("HOME", envs)) == -1)
			return(print_error("minishell: cd: HOME not set\n"));
	}
	else if(strcmp(new_dir, "-") == 0) // go to OLDPWD
	{
		if(chdir(get_env_value("OLDPWD", envs)) == -1)
			return(print_error("minishill: cd: OLDPWD not set\n"));
		printf("%s\n", get_env_value("OLDPWD", envs));
	}
	else if(chdir(new_dir) == -1) // go to path , relative or absoulot 
	{
		perror("minishell");
		return(EXIT_FAILURE);
	}
}

int ft_cd(char **args, t_env *envs)
{
	char (*pwd), (*oldpwd);
	int i;

	i = 0;
	while (args[i] != NULL) // len args
		i++;
	if(i > 2)
		return(print_error("minishell: cd: too many arguments\n"));
	oldpwd = get_env_value("PWD", envs); // we do both methods , when getcwd can't retrive the pwd form kernel
	if(oldpwd == NULL)
	go_new_dir(args[1]);
	pwd = getcwd(NULL, 0);
	if(pwd == NULL) // when getcwd failed
	{
		perror("minishell");
		return(EXIT_FAILURE);
	}
	set_env("OLDPWD", oldpwd, envs); //not check oldpwd ,if not exist
	set_env("PWD", pwd, envs);
	return(EXIT_SUCCESS);
}
