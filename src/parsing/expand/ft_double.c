/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:35:55 by marvin            #+#    #+#             */
/*   Updated: 2025/05/08 18:35:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int ft_double(char *str, t_env *envp, int k, int m)
{
    int i;
    int j;
    t_env *tmp;
    char **s;

    // (void)k;
    s = malloc((ft_strlen(str) + 1 )* sizeof(char *));
    i = 0;
    s[k] = malloc (ft_strlen(str) + 1);
    while(str[i])
    {
        if(str[i] != '$')
        {
            s[k][m++] = str[i];
            if(str[i + 1] == '$'|| !str[i + 1])
            {
                s[k][m] = 0;
                printf("%s",s[k]);
                k++;
                s[k] = malloc (ft_strlen(str) + 1);
            }
        }
        else if(str[i] == '$')
        {
            m = 0;
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
                // i = j;
                while((str[j] != ')'))
                {  
                    if(str[j] == 0)
                        return(error_print("syntax error \"unclosed parentheses\"\n"),2);
                    j++;
                }
                i = j + 2;
                s[k][0] = '0';
                s[k][1] = 0;
                printf("%s",s[k]);
                k++;
                s[k] = malloc (ft_strlen(str) + 1);
                continue;
            }
            else if(str[j] == '(')
            {
                m = 0;
                j++;
                i = j;
                while(str[j] != ')')
                {
                    if(str[j] == 0)
                        return(error_print("syntax error \"unclosed parentheses\"\n"),2);
                    j++;
                }
                while(str[i] == ' ')
                    i++;
                while(i <= j)
                {
                    if(str[i] == '(')
                        i++;
                    if(str[i] == ')')
                    {
                        s[k][m] = 0;
                        break;
                    }    
                    s[k][m] = str[i];
                    m++;
                    i++;
                }
            }
            if(s[k][m] != 0)
                s[k][m] = 0;
            printf("%s",s[k]);
            k++;
            s[k] = malloc (ft_strlen(str) + 1);
            if(str[j] < 'A' ||str[j] > 'Z')
                break;
            i = j;
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
                    if(ft_strncmp(tmp->key,str + j,(ft_strlen(tmp->key) + 1)) == 0)
                    {
                        s[k] = malloc (ft_strlen(tmp->value) + 1);
                        s[k] = ft_strdup(tmp->value);
                        printf("%s",s[k]);
                        k++;
                        s[k] = malloc (ft_strlen(str) + 1);
                        j += (int)ft_strlen(tmp->key);
                        i = j;
                        break;
                    }
                    tmp = tmp->next;
                }
                if(!tmp)
                {

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
    printf(" ");
    return(0);
}
