#include "../../../includes/minishell.h"

t_env *split_key_value(int is_path_exported, char *env, char **envp)
{
	t_env		*newnode;
	char 		*value;
	char 		**key;

	newnode = (t_env *)malloc(sizeof(t_env));
	if(!newnode)
		return(NULL);
	value = ft_strchr(env, '='); // search for the fisrt (=) and return pointer to it
	key = ft_split(env, '='); // split the command with (=);
	if(!key)
		return(NULL);
	newnode->key = ft_strdup(key[0]); //duplicate the first argument
	newnode->value = ft_strdup(value + 1); //dup the string, +1 to skiip (=), like (=/hind/....)
	newnode->next = 0;
	if(ft_strcmp(newnode->key, "PATH") == 0 && (!envp || !envp[0]) && !is_path_exported) // flaged with 2 to not printed in (env, export)
	{
		newnode->flag_exported = 2;
		is_path_exported = 1;
	}
	else
		newnode->flag_exported = 1; //if has a value (true)
	return(newnode);
}

t_env *new_env(char *env, char **envp)
{
	static int 	is_path_exported;
	t_env		*newnode;
	
	newnode = (t_env *)malloc(sizeof(t_env));
	if(!newnode)
		return(NULL);
	if(ft_strchr(env, '=') != NULL)
		newnode = split_key_value(is_path_exported, env, envp);
	else
	{
		newnode->key = ft_strdup(env); //duplicate env 
		newnode->value = NULL; // no value. 
		newnode->flag_exported = 0; //if just the key (false)
		newnode->next = 0;
	}
	return(newnode);
}

void add_env(t_env *newnode, t_env **head_list)
{
	t_env *temp;

	temp = (*head_list);
	if(temp ==  0)
	{
		(*head_list) = newnode;
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = newnode;
	}
}

char *get_pwd()
{
	char *working_d;
	char *complet_pwd;

	working_d = getcwd(NULL, 0);
	if(!working_d)
	{
		perror("minishell");
		return(NULL);
	}
	complet_pwd = ft_strjoin("PWD=", working_d);
	free(working_d);
	return(complet_pwd);
}
