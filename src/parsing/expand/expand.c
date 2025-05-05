/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:31:13 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/05 18:48:25 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
int check_operator(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' )
        return(1);
    return(0);
}
void operation(char *str,int i, int j)
{
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
                if(check_parth(str + i) == 0)
                    return(error_print("syntax error \"unclosed parentheses\"\n"),NULL);
                if(str[j] == '(' && str[j + 1] == '(')
                {
                    j+= 2;
                    i = j;
                    while((str[j] != ')'))
                    {  
                        if(check_operator(str[j]) != 1 && !(str[j] >= '0' && str[j] <= '9') && str[j] != ' ')
                            return(printf("0\n"),NULL);
                        if(str[j] == 0)
                            return(error_print("syntax error \"unclosed parentheses\"\n"),NULL);
                        j++;
                    }
                    // if(str[i] != ')' || str[i + 1] != ')')
                    //     return(error_print("syntax error \"unclosed parentheses\"\n"),NULL);
                    while(str[i] == ' ')
                        i++;
                    operation(str,i,j);              
                    
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
