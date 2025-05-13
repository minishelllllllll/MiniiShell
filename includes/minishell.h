
#ifndef MINISHELL_H
#define MINISHELL_H

#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

#include <errno.h>
extern char **environ;
#include <sys/wait.h>


typedef struct s_parsing
{
    int index;
    char *content;
    char *type;
    char  *state;
    struct s_parsing *next;
}t_parsing;


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
int ft_pwd(t_env *envs);
int ft_env(t_env *envs);
int ft_exit(char **args);
int ft_cd(char **args, t_env *envs);
int ft_unset(char **args, t_env **envs);
int ft_export(char **args, t_env **envs);

void add_env(t_env *newnode, t_env **head_list);

t_env  *list_envs(char **envp);
t_env *new_env(char *env); //0 if a normal env //1 if exported (just the name) 
void	free_list(t_env **head_env);
void free_node(t_env *newnode);
char *get_env_value(char *key, t_env *envs);

int check_flag_n(char *str);
int ft_builtin(char **command, t_env **envs);

#endif