/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:47:30 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/30 13:01:51 by marvin           ###   ########.fr       */
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


int *saved_stdin_out(void)
{
    int *in_out;

    in_out = (int *)malloc(sizeof(int) * 2);

    in_out[0] = dup(STDIN_FILENO);
    in_out[1] = dup(STDOUT_FILENO);
    if(in_out[0] == -1 || in_out[1] == -1)
        perror("minishell");
    return(in_out);
}

void restore_stdin_out(int *saved_stdin_out)
{
    if(dup2(saved_stdin_out[0], STDIN_FILENO) == -1)
        perror("dup2 ");
    if(dup2(saved_stdin_out[1], STDOUT_FILENO) == -1)
        perror("dup2 ");
    close(saved_stdin_out[0]);
    close(saved_stdin_out[1]);
}

char *shell_prompt(t_env *envs)
{
	char *cwd;
	char *prompt;

	cwd = getcwd(NULL, 0);
	if(!cwd)
		cwd = get_env_value("PWD", envs);
	prompt = ft_strjoin(cwd, " $> ");
	return(prompt);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char    *rdl;
	t_env *envs;
    t_parsing *head;
    t_cmd *cmd = NULL;

	t_env   *envs;
	t_cmd   *commads_in_out;

    int     *arr_in_out;
    t_pids  *pids; // struct of process ids 

	envs = list_envs(envp); //save

	while (1)
	{
        arr_in_out = saved_stdin_out();  //save
        if(arr_in_out[0] == -1 || arr_in_out[1] == -1)
        {
            free(arr_in_out);
            free_list(&envs);
            return 0;
        }

		rdl = readline(shell_prompt(envs));
		if (!rdl)  // Handle Ctrl+D (EOF)
		{
			printf("exit\n"); // notify message
			break;
		}
		// parssing command by pipe and space
        head = lexer(rdl);
		if(skip_space_str(str) == 1)
            add_history(str);
        if(checker(head,envs,ft_strlen(str),&cmd) == 2)
            continue;
        commads_in_out = cmd;
        
        //execution
        if(commads_in_out)
        {
            pids = execute_commands(&envs, commads_in_out);
            if(!pids)
                return(0);       
            restore_stdin_out(arr_in_out);
            waiting_childs(pids);
        }

	}
	return (0);
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
    return (0);
}

/*
///////////////////////
unset $(env | cut -d= -f1)
( echo "$USER $PATH" > file | grep usr << limiter | wc -l < file >> out_file )
[ < file wc -l < file > out_file ]
//////////////////////

handle exit status  ~
    --> export should return with failure when not a valid name , but at same time should continue execution when i have many args.
    (export 2A=1 B=1 --> error msg + exit fail 1 + B exported)
    /////////////////////////////////////////
    >> export 2A=22 B=22
    bash: export: `2A=22': not a valid identifier
    >> echo $?
    1
    >> export | grep B
    declare -x B="22"
    ///////////////////////////////////////// solution (edit GLOBAL status)

    --> env with args (correct or not) should return error ?
    (cases when env used with command ) fix it eith childs also

    --> check exit status of childs proccess is return it correctly 



exit (argument + overflow) ~

handle signals ~

garbeg collectore ~


handell redirections ~solved~

handel heredoc ~solved~

split functions ~done~

handle waitpid ~solved~
-> store the pids ~ done ~
void	wait_procces(int pid)
{
    int	st;
    int	i;

    i = 0;
    waitpid(pid, &st, 0);
    if (WEXITSTATUS(st))
        MY_EXIT_STATUS = WEXITSTATUS(st);
    if (WIFSIGNALED(st))
    {
        MY_EXIT_STATUS = st + 128;
        if (MY_EXIT_STATUS == 131)
            printf("Quit: 3\n");
    }
    while (wait(&st) > i)
        i = 0;
}

error handling, in all functions  ~ 
--> handle close behave -> remove close from duplication ~done~ .
--> check envs in builtins . ~done~
-----> env should not work with envs==NULL ~solved~
-----> perror or strerror instead of printf ~solved~


*/
