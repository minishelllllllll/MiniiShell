/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:44:37 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/01 18:48:05 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_pipe(char *str)
{
    int i;
    int j;
    int a;

    i = 0;
    a = 0;
    while(str[i] == ' ')
            i++;
    j = i;
    while(str[i])
    {
        if(str[j] == '|' || str[i] == '|')
        {
            if(str[i] == '|')
            {
                a = i + 1;
                while(str[a])
                {
                    if(str[a] != ' ')
                        break;
                    a++;
                }
                if(str[a] == '|')
                {
                    error_print("syntax error near unexpected token '|'\n");
                    return(1);
                }
            }
            if(str[a] == 0 || str[j] == '|')
            {
                error_print("syntax error near unexpected token '|'\n");
                return(1);
            }
        }
        i++;
    }
    return(0);
}