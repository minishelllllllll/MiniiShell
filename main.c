/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:47:30 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/02 17:52:46 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main()
{
    char *str;
    t_parsing *head;

    while(1)
    {
        str = readline("minishell :");
        // r = check_pipe(str);
        // r = check_redirection_pipe(str);
        // r = check_redirection(str);
        // r = check_redir_end(str);
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
        if(syntax_err(head) == 0)
            return(0);
        
    }
    return(1);
}

