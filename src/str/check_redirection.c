/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:07:49 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/02 17:32:06 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_redir_end(char *str)
{
    int len;

    len = ft_strlen(str) - 1;
    while(len >= 0)
    {
        if(str[len] != ' ')
            break;
        len--;
    }
    if(str[len] == '<' && str[len - 1] == '>')
            return(error_print("syntax error near unexpected token '<'\n"),1);
    else if((str[len] == '>' && str[len - 1] == '>') || (str[len] == '<' && str[len - 1] == '<'))
        return(error_print("syntax error near unexpected token 'newline'\n"),1);
    else if((str[len] == '>' || str[len] == '<') || (str[len] == '<' && str[len - 1] == '>'))
        return(error_print("syntax error near unexpected token 'newline'\n"),1);
    else
        return(0);
}
int check_redir(char *str,int i)
{
    while(str[i] == ' ')
        i++;
    if(str[i] == '>' || str[i] == '<')
    {
        error_print("syntax error near unexpected token '");
        write(2,&str[i],1);
        write(2,"'\n",2);
        return(1);
    }
    else if(str[i] == '>' && str[i + 1] == '>')
    {
        error_print("syntax error near unexpected token ");
        ft_putstr_fd("'>>' \n",2);
        return(1);
    }
    else if(str[i] == '<' && str[i + 1] == '<')
    {
        error_print("syntax error near unexpected token ");
        ft_putstr_fd("'<<' \n",2);
        return(1);
    }
    else if(str[i] == '<' && str[i + 1] == '>')
    {
        error_print("syntax error near unexpected token ");
        ft_putstr_fd("'<>' \n",2);
        return(1);
    }
    else if(str[i] == '>' && str[i +  1] == '<')
    {
        error_print("syntax error near unexpected token '>' \n");
        return(1);
    }
    return(0);
}
// int check_redirection(char *str)
// {
//     int i;
//     int r;
//     char c;

//     i = 0;
//     r = 0;
//     while(str[i] == ' ')
//         i++;
//     while(str[i])
//     {
//         if(str[i] == '"' || str[i] == '\'')
//         {
//             c = str[i++];
//             while(str[i] != c)
//             {
//                 if(!str[i])
//                     break;
//                 i++;
//             }
//         }
//         if((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
//         {
//             i = i + 2;
//             r = check_redir(str,i);
//             if(r == 1)
//                 return(1);
//         }
//         if(str[i] == '>' || str[i] == '<')
//         {
//             i++;
//             r = check_redir(str,i);
//             if(r == 1)
//                 return(1);
//         }
//         i++;
//     }
//     return(0);
// }
int check_redirection_pipe(char *str)
{
    int i;
    char c;

    i = 0;
    while(str[i] == ' ')
        i++;
    while(str[i])
    {
        if(str[i] == '"' || str[i] == '\'')
        {
            c = str[i++];
            while(str[i] != c)
            {
                if(!str[i])
                    break;
                i++;
            }
        }
        if(str[i] == '|' && i >= 1)
        {
            i--;
            while(str[i] == ' ' && i >= 0)
                i--;
            if((str[i] == '<' && str[i - 1] == '<') || ((str[i] == '>' && str[i - 1] == '>')) )
            {
                error_print("syntax error near unexpected token '|'\n");
                return(1);
            }
            if(str[i] == '<' || str[i] == '>')
            {
                error_print("syntax error near unexpected token '|'\n");
                return(1);
            }
            i += 2;
        }
        i++;
    }
    return(0);
}