#include "../../../includes/minishell.h"


t_env  *list_envs(char **envp)
{
	char	**minimal_envp;

	if(!envp) // if all envps removed 
		return(NULL);
	else if(envp[0] == NULL) // cuz a char *envp[] = { NULL }; (start with minimal envps)
	{
		minimal_envp = creat_mini_envp();
		return(build_new_envs(minimal_envp, envp));
	}
	else
		return(build_new_envs(envp, envp));
}

char **creat_mini_envp()
{
	char	**minimal_envp;

	minimal_envp = malloc(sizeof(char *) * 5);
	minimal_envp[0] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	minimal_envp[1] = ft_strdup("OLDPWD");
	minimal_envp[2] = get_pwd();
	minimal_envp[3] = ft_strdup("SHLVL=1");
	minimal_envp[4] = NULL;
	return(minimal_envp);
}



t_env  *build_new_envs(char **envs, char **envp)
{
	t_env	*head_env;
	t_env	*newnode;
	int i;

	head_env = 0;
	i = 0;
	while (envs[i])
	{
		newnode = new_env(envs[i], envp);
		if(!newnode)
		{
			free_list(&head_env); //garbeg coll
			return(NULL);
		}
		add_env(newnode, &head_env);
		i++;
	}
	return(head_env);
}

