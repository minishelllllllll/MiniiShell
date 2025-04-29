
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
int ft_echo(char **args);
int ft_pwd();

#endif