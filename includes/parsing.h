#ifndef PARSING_H
#define PARSING_H

#include <readline/readline.h>
#include <readline/history.h>

enum e_type
{
   WORD = -1,
   WHITE_SPACE = ' ',
   NEW_LINE = '\n',
   QUOTE = '\'',
   DQUOTE = '\"',
   ESCAPE = '\\',
   ENV = '$',
   EXIT_STATUS,
   PIPE_LINE = '|',
   REDIR_IN = '>',
   REDIR_OUT = '<',
   HERE_DOC = -2,
   DREDIR_OUT = -3,
   AND,
};

enum e_state
{
    GENERAL = 0,
    INQUOTE = 1,
    INDQUOTE = 2
};

typedef struct s_lexer
{
    char *str;
    int len;
    int index;
}t_lexer;


typedef struct s_parsing
{
    char *content;
    enum e_type type;
    enum e_state state;
    struct s_parsing *next;

}t_parsing;

t_parsing *lexer(char *str);
t_parsing *ft_save(char *av,t_parsing *head,enum e_type type,char c,enum e_state state);
enum e_type check_token(char *str, int i);
void    error_print(char *str);
int syntax_err(t_parsing *head,char **envp);
t_parsing *check_pipe(t_parsing *curr, int len);
t_parsing *check_quote(t_parsing *curr);
t_parsing *skip_space(t_parsing *head);
t_parsing *check_redirection(t_parsing *curr);
t_parsing *expand(t_parsing *head, char **envp);
#endif