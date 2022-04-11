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
# include <fcntl.h>

// enum lexer
typedef enum type{
 	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_MINUS = '-',
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

// redirection struct
typedef struct redirection
{
	int		*type;
	char	**file;
	void	*next;
}	t_red;

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
void	free_env(t_env **env);

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

//analyser
void	get_token_in_qoute(t_lst **s);
int	lstsize(t_lst **s);
int lst_del(t_lst **s, int pos);
t_lst   **get_lst_pos(t_lst **s);
void    get_qoute(t_lst **s);

//analyser utils
char	*ft_strjoin_v2(char *s1, char *s2);
int	lstsize(t_lst **s);
int lst_del(t_lst **s, int pos);
t_lst   **get_lst_pos(t_lst **s);
void    del_prev(t_lst *lst, t_lst **s);
int	ft_strlen_v2(const char *str);
void    free_lst(t_lst **s);
void    add_lst(t_lst *lst);

//get quote protos;
void    get_quote_case_1(t_lst *lst, t_lst **s);
void    get_quote_case_2(t_lst *lst, t_lst **s);


// get variable protos;
void    get_variable(t_lst **s);
void    translate_variable(t_lst **s, t_env **env);
void    get_variable_case_1(t_lst *lst, t_env *tmp, t_lst **s);
void    get_variable_case_2(t_lst *lst, t_env *env, char *tmp2, int i);
void    get_variable_in_quote(t_lst **s, t_env **envp);

//get command protos;
char	*find_path(char **env);
void	free_tab(char **path_tab);
char	*get_cmd(char **envp, char *cmd);
char	**get_array_execve(t_lst *lst, t_lst **s);
void	ft_exec_cmd(t_lst *lst, char **envp, char **cmd);
char 	*ft_strndup(const char *s, int n);
char	*ft_strncpy(char *dst, const char *src, size_t n);

//init simpple cmd && reddirection array
int    get_redirection_with_file(t_lst **s);
int get_nb_red_lst(t_lst **s);
t_red	**get_red_array(t_lst **s);
t_red    **get_red_array_data(t_lst **s, t_red **f);
int    get_simple_cmd_array_size(t_lst **s);
char    **get_simple_cmd_array(t_lst **s);
int check_red_token(t_lst **s);
void    if_only_red(t_lst **s);

// reddirection.c
void    ft_exec(t_red **s, char **simple_cmd, char **envp);
int		red_dup_mannager(t_red *red, int fd_ret, int i);
void    case_1_ft_exec(t_red *red, char **simple_cmd, int i, char **envp, int save_out);
void    case_2_ft_exec(t_red *red, char **simple_cmd, int i, char **envp, int save_out);
void    case_3_ft_exec(t_red *red, char **simple_cmd, int i, char **envp, int save_out);
void    case_4_ft_exec(t_red *red, char **simple_cmd, int i, char **envp, int save_out);
void    free_red(t_red **s);
void    dup_mannager_out(t_red *red, int i, int save_out, char *cmd);
int check_ambigous_redirect(t_red **s);

#endif