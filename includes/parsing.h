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
   DREDIR_IN = -3
};

enum e_state
{
    GENERAL = 0,
    INQUOTE = 1,
    INDQUOTE = 2,
    ENV_STRING = 3
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

typedef struct s_var
{
    char **s;
    int y;
    int z;
    char *s1;
    int in_file;
    int out_file;
    int k;
    int m;
    int i;
    int j;
    int l;
}t_var;

int is_allowed(char c);
t_parsing *lexer(char *str);
t_parsing *ft_save(char *av,t_parsing *head,enum e_type type,char c,enum e_state state);
enum e_type check_token(char *str, int i);
void    error_print(char *str);
t_parsing *check_pipe(t_parsing *curr, int len);
t_parsing *check_quote(t_parsing *curr);
t_parsing *skip_space(t_parsing *head);
t_parsing *check_redirection(t_parsing *curr);
int is_allowed(char c);
int syntax_err(t_parsing *head);
int ft_redirect_in(t_parsing *head);
int	ft_check_env(const char *s1, const char *s2, size_t n);
#endif