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

	envs = list_envs(envp);
    while(1)
    {
        str = readline("minishellox :");
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
        checker(head,envs,ft_strlen(str));
            // return(0);        
    }
    ft_export(av, &envs);
	free_list(&envs);
}

//garbege collector 
//norrrrmineeetee waaaa