/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:47:30 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/04 15:22:54 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int ac,char **av,char **envp)
{
    char *str;
    t_parsing *head;
    (void)ac;
    (void)av;
    while(1)
    {
        str = readline("minishell :");
        head = lexer(str);
        // t_parsing *curr = head;
        // while(curr)
        // {
        //     printf("content ==> %s\n",curr->content);
        //     printf("state ==> %d\n",curr->state);
        //     printf("type ==> %c\n",curr->type);
        //     printf("****************************\n");
        //     curr = curr->next;
        // }
        syntax_err(head,envp);
            // return(0);
        
    }
    return(1);
}

