
#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include "parsing.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <errno.h>
extern char **environ;
#include <sys/wait.h>

typedef struct s_cmd    
{
	int				in_file;
	int				out_file;
	char				**full_cmd;
	struct s_cmd	*next;
}					t_cmd;

// typedef struct s_parsing
// {
//     char *key;
//     char *value;
//     struct env *next;
// } t_env;


//execution
typedef struct env
{
    char    *key;
    char    *value;
    int     flag_exported;
    struct env *next;
}  t_env;


int	ft_strcmp(char *s1, char *s2);


int ft_echo(char **args);
int ft_pwd();
int ft_env(t_env *envs);
int ft_exit(char **args);
int ft_cd(char *path, t_env *envs);
int ft_unset(char **args, t_env **envs);
int ft_export(char **args, t_env **envs);

void add_env(t_env *newnode, t_env **head_list);

t_env  *list_envs(char **envp);
t_env *new_env(char *env); //0 if a normal env //1 if exported (just the name) 
void	free_list(t_env **head_env);
void free_node(t_env *newnode);


//parsing

int  checker(t_parsing *head,t_env *envp, int len,t_cmd *cmd);
t_parsing *expand(t_parsing *head,t_env *envp,t_var *data,t_cmd *cmd);
int ft_double(char *str, t_env *envp, t_var *data);
int check_expand(t_parsing *head,t_env *envp,int len,t_cmd *cmd);
t_cmd *ft_send(t_var *data, t_cmd *cmd);
#endif