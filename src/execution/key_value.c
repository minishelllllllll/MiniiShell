#include "../../includes/minishell.h"

void	free_list(t_env **head_env)
{
	t_env	*temp;
	t_env	*next;

	temp = (*head_env);
	while (temp != NULL)
	{
		next = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
		temp = next;
	}
	(*head_env) = NULL;
}

t_env *new_env(char *env)
{
	t_env	*newnode;
	char 	*value;
	char 	**key;
	
	value = ft_strchr(env, '='); // search for the fisrt (=) and return pointer to it;

	key = ft_split(env, '='); // split the command with (=);
	if(!key)
		return(NULL);

	newnode = (t_env *)malloc(sizeof(t_env));
	if(!newnode)
	{
		// free_2d(key);
		return(NULL);
	}

	newnode->key = ft_strdup(key[0]); //duplicate the first argument
	newnode->value = ft_strdup(value + 1); //dup the string, +1 to skiip (=), like (=/hind/....)
	newnode->next = 0;

	// free_2d(key);
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

t_env  *list_envs(char **envp)
{
	t_env	*head_env;
	t_env	*newnode;
	int		i;

	head_env = 0;
	i = 0;
	while (envp[i])
	{
		newnode = new_env(envp[i]);
		if(!newnode)
		{
			free_list(&head_env);
			return(NULL);
		}
		add_env(newnode, &head_env);
		i++;
	}
	// print_env_list(head_env);
	return(head_env);
}


void	print_env_list(t_env *head)
{
	t_env *temp;

	temp = head;
	while (temp)
	{
		printf("key: %s | value: %s\n", temp->key, temp->value);
		temp = temp->next;
	}
}