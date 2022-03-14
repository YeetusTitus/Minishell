#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ft_libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <stdlib.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <string.h>
# include <stddef.h>


// enum lexer
typedef enum type{
 	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_QOUTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
    CHAR_WILDCART = '*',
    CHAR_LPARENTHESIS = '(',
    CHAR_RPARENTHESIS = ')',
	CHAR_EQUAL = '=',
	CHAR_DOLLAR = '$',
    CHAR_NULL = 0
//	TOKEN	= -1,
} token_type;


// lexer struct

typedef struct s_lst
{
    struct s_lst   *prev;
    struct s_lst   *next;
    char            *data;
    int             type;
	int				pos;
}   t_lst;

// env struct 
typedef struct s_token
{
	char			error;
	char			type;
	void			*content;
	void			*next;
}	t_token;

typedef struct s_command
{
	char	**path;
	int		nbr;
	char	***toexec;
}	t_command;

typedef struct s_env
{
	char	*name;
	char	*content;
	void	*next;
}	t_env;

// env/envutils
t_env	*envnew(char *name, char *content);
int		envsize(t_env *lst);
t_env	*envlast(t_env *lst);
void	envadd_back(t_env **alst, t_env *new);
void	envadd_front(t_env **alst, t_env *new);

// env/createenv
int		lenachr(char *str, char chr);
int		lenbchr(char *str, char chr);
char	**content_env(char **cont, char *line);
int		create_env(t_env **env, char **envp);

// env/export
int		env_exist(t_env *env, char *name);
void	export(t_env *env, char *name, char *content);
void	print_env(t_env *env);


// ----------------------------------------------------------------


// lexer
void    ft_loop(char **envp);
t_lst  **get_data_in_lst(char *str);
int  *get_enum_data(char *str);
void    free_lst(t_lst **s);
//void    free_array(int *array);

//analyser
void	get_token_in_qoute(t_lst **s);
int	lstsize(t_lst **s);
int lst_del(t_lst **s, int pos);
t_lst   **get_lst_pos(t_lst **s);

//analyser utils
char	*ft_strjoin_v2(char *s1, char *s2);
int	lstsize(t_lst **s);
int lst_del(t_lst **s, int pos);
t_lst   **get_lst_pos(t_lst **s);

#endif

