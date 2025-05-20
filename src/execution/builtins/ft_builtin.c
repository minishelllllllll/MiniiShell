#include "../../../includes/minishell.h"

int ft_builtin(char **command, t_env **envs)
{
	if(ft_strcmp(command[0], "cd") == 0)
		return(ft_cd(command, (*envs)), 0);

	else if(ft_strcmp(command[0], "pwd") == 0)
		return(ft_pwd((*envs)), 0);

	else if(ft_strcmp(command[0], "env") == 0)
		return(ft_env((*envs)), 0);

	else if(ft_strcmp(command[0], "exit") == 0)
		return(ft_exit(command), 0);

	else if(ft_strcmp(command[0], "unset") == 0)
		return(ft_unset(command, envs), 0);
		
	else if(ft_strcmp(command[0], "export") == 0)
		return(ft_export(command, envs), 0);
	
	else if(ft_strcmp(command[0], "echo") == 0)
		return(ft_echo(command), 0);
	else
		return(-1);
}

int is_parent_builtin(char *cmd)
{
	if(ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "unset") == 0 ||
		ft_strcmp(cmd, "exit") == 0 )
		return(0);
	return(-1);
}
