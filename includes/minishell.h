
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

//parsing
void    parsing(int ac,char **av);
size_t	ft_strlen(const char *s);
t_parsing *test(int ac,char *av,t_parsing *head, int i);
int search_pipe(char *str);


//execution
typedef struct env
{
    char *key;
    char *value;
    struct env *next;
} t_env;

int ft_echo(char **args);
int ft_pwd();
int ft_env(t_env *envs);
int ft_exit(char **args);
int ft_cd(char *path, t_env *envs);
int ft_unset(char **args, t_env *envs);

t_env  *list_envs(char **envp);

#endif