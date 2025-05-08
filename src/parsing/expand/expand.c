/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:31:13 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/06 18:51:16 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int check_parth(char *str)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while(str[i])
    {
        if(str[i] == '(')
            len++;
        i++;
    }
    i = 0;
    while(str[i] && len >= 0)
    {
        if(str[i] == ')')
            len--;
        i++;
    }
    if(len != 0)
        return(0);
    return (1);
}
t_parsing *expand(t_parsing *head,t_env *envp)
{
    char *str;
    int i;
    int j;
    t_env *tmp;

    if(!head)
        return(NULL);
    if(head->state == 2)
    {
        str = head->content;
        i = 0;
        while(str[i] == ' ')
            i++;
        while(str[i])
        {
            if(str[i] != '$')
                printf("%c",str[i]);
            else if(str[i] == '$')
            {
                j = i;
                j++;
                if(str[j] == '\0') 
                {
                    printf("$"); 
                    break;
                }
                if(str[j] == '(' && str[j + 1] == '(')
                {
                    j+= 2;
                    i = j;
                    while((str[j] != ')'))
                    {  
                        if(str[j] == 0)
                            return(error_print("syntax error \"unclosed parentheses\"\n"),NULL);
                        j++;
                    }
                    return(printf("0\n"),NULL);             
                }
                else if(str[j] == '(')
                {
                    j++;
                    i = j;
                    while(str[j] != ')')
                    {
                        if(str[j] == 0)
                            return(error_print("syntax error \"unclosed parentheses\"\n"),NULL);
                        j++;
                    }
                    while(str[i] == ' ')
                        i++;
                    while(i <= j)
                    {
                        if(str[i] == '(')
                            i++;
                        if(str[i] == ')')
                            break;
                        printf("%c",str[i]);
                        i++;
                    }
                }
                if(str[j] < 'A' ||str[j] > 'Z')
                    break;
                i = j;
                // while(str[i])
                // {
                //     if(str[i] == ' ' ||( !(str[i] >= 'A' && str[i] <= 'Z' ) && str[i] != '_'))
                //         break;   
                //     i++;
                // }
                if(is_allowed(str[i]) == 1)
                {
                    i++;
                    continue;  
                }
                else
                {
                    tmp = envp;
                    while(tmp)
                    {
                        // printf("key - >%s\n",tmp->key);
                        // printf("str - >%s\n",str + j);
                        if(ft_strncmp(tmp->key,str + j,(ft_strlen(tmp->key) + 1)) == 0)
                        {
                            printf("%s",tmp->value);
                            j += (int)ft_strlen(tmp->key);
                            i = j;
                            break;
                        }
                        tmp = tmp->next;
                    }
                    if(!tmp)
                    {
                        // printf("%c\n",str[i]);
                        while(str[i] != ' ' && str[i])
                            i++;
                    }
                    if(str[i] != 0)
                        continue;
                    else
                        break;
                }    
            }
            i++;
        }
        printf("\n");
    }
    if(head->state == 1)
        return(printf("%s\n",head->content),NULL); 
      
    return(head);
}
