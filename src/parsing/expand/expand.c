/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:31:13 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/04 18:34:53 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_parsing *expand(t_parsing *head,char **envp)
{
    char *str;
    int i;
    int j;
    t_env *res;
    (void)envp;
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
                // if(str[j] == '(' && str[j + 1] != '(')
                //     i++;
                if(str[j] == '(' && str[j + 1] == '(')
                {
                    j+= 2;
                    i = j;
                    while((str[j] != ')' && str[j + 1] != ')' )|| str[j] != ')')
                    {
                        if(str[j] == 0)
                            return(error_print("syntax error \"unclosed parentheses\"\n"),NULL);
                        j++;
                        if(str[j] != ')' && str[j + 1] == ')')
                            j++;
                    }
                    while(str[i] == ' ')
                        i++;
                    while(i <= j)
                    {
                        if(str[i] == ')')
                            break;
                        printf("%c",str[i]);
                        i++;
                    }
                    
                    if(str[j] != ')' || str[j + 1] != ')')
                        return(error_print("syntax error \"unclosed parentheses\"\n"),NULL);
                    
                }
                if(str[j] < 'A' ||str[j] > 'Z')
                    break;
                res = list_envs(envp);
                i = j;
                while(str[i])
                {
                    if(str[i] == ' ' ||( !(str[i] >= 'A' && str[i] <= 'Z' ) && str[i] != '_'))
                        break;   
                    i++;
                }
                if(is_allowed(str[i]) == 1)
                {
                    i++;
                    continue;  
                }
                else
                {
                    while(res)
                    {
                        if(ft_strncmp(res->key,str + j,(i - j)) == 0)
                        {
                            printf("%s",res->value);
                            break;
                        }
                        res = res->next;
                    }
                    if(str[i] != 0)
                        continue;  
                }    
            }
            i++;
        }
        printf("\n");
        // return(printf("%s\n",head->content),NULL);    
    }
    if(head->state == 1)
        return(printf("%s\n",head->content),NULL);    
    return(head);
}
