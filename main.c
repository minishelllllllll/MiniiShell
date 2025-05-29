/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:47:30 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/06 19:00:19 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <readline/history.h>
// ""$USER"
// check this case
int skip_space_str(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] != ' ')
            return(1);
        i++;
    }
    return(0);
}
int main(int ac, char **av, char **envp)
{
    (void)ac;
	t_env *envs;
    char *str;
    t_parsing *head;
    t_cmd *cmd = NULL;

	envs = list_envs(envp);
    while(1)
    {
        str = readline("minishellox :");
        if(!str)
            continue;
        head = lexer(str);
        t_parsing *curr = head;
        
        while(curr)
        {
            printf("content ==> %s\n",curr->content);
            printf("state ==> %d\n",curr->state);
            printf("type ==> %c\n",curr->type);
            printf("****************************\n");
            curr = curr->next;
        }
        if(skip_space_str(str) == 1)
            add_history(str);
        if(checker(head,envs,ft_strlen(str),&cmd) == 2)
            continue;
        t_cmd *c = cmd;
        int i =0 ;
        while(c)
        {
            i = 0;
            while(c->full_cmd[i])
                printf("full cmd => %s \n",c->full_cmd[i++]);
            printf("in_file => %d\n",c->in_file);
            printf("out_file => %d\n",c->out_file);
            printf("****************************\n");
            c = c->next;
        }       
    }
    ft_export(av, &envs);
	free_list(&envs);
}

//garbege collector 
//norrrrmineeetee waaaa

// export v="ls -la"
// $v should execute
// $v hi should seperate
