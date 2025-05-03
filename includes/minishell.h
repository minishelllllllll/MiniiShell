
#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include "parsing.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>

//execution
typedef struct env
{
    char *key;
    char *value;
    struct env *next;
} t_env;


void add_env(t_env *newnode, t_env **head_list);

t_env  *list_envs(char **envp);
t_env *new_env(char *env);
void	free_list(t_env **head_env);
void	print_env_list(t_env *head);
#endif