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
//# include <curses.h>
# include <term.h>
# include <string.h>
# include <stddef.h>
# include <fcntl.h>


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
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

//global pour les signaux
extern int	g_sign;

// env/envutils
t_env			*envnew(char *name, char *content);
int				envsize(t_env *lst);
t_env			*envlast(t_env *lst);
void			envadd_back(t_env **alst, t_env *new);
void			envadd_front(t_env **alst, t_env *new);

// env/envutils2
t_env			*envname(t_env **env, char *name, int colonne);
void			free_env(t_env *env);
void			free_export(t_env **env);

// env/createenv
int				lenachr(char *str, char chr);
int				lenbchr(char *str, char chr);
char			**content_env(char **cont, char *line);
void			create_env2(t_env **env);
int				create_env(t_env **env, char **envp);

// env/export
int				env_exist(t_env **env, char *name);
int				export(t_env **env, char *name, char *content);
int				export_env(t_env **env, char *name, char *content);
void			print_env(t_env *env);
void			print_export(t_env **env);

// env/unset
int				unset(t_env **env, char *name);
int				unset_export(t_env **env, char *name);
int				unset_env_set(t_env **env, char *name, int column);

// utils/utils1
//int				ft_strcmp(char *str1, char *str2);
char			**ft_malloc_error(char **tabl, int size);
int				tablen(char **tabl);

// path/cd
int				cd(t_env **env, char *path);
void			cwdisdel(t_env **env);
void			envcwd(t_env **env, char *path);
void			envoldpwd(t_env **env);
void			envoldpwd2(t_env **env);

// path/pwd
int				pwd(t_env **env);

// echo
void			ms_echo(char **table);

// signals/signals
void			handler_sig(int num);
void			sign_onoff(int toogle);
// declaration replace line
void			rl_replace_line(const char *text, int clear_undo);

// signals/exit
void			ms_exit(char **table, t_env **env);
int				exit_error(char **table);

// signals/exit_utils
unsigned char	ms_atouc(char *str);
int				verif_maxlong2(char *nbr, int neg);
int				verif_maxlong(char *nbr);
int				verif_isdigit(char *str);


// ----------------------------------------------------------------

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

//get_variable_in_quote struct
typedef struct s_variable
{
	int		i;
	int		j;
	int		len;
	char	*tmp;
}	t_variable;

// exec struct
typedef struct exec
{
	int	i;
	int	save_in;
	int	save_out;
	int	fd[2];
	int	ret;
}	t_exec;

// simple_cmd struct
typedef struct s_cmd
{
	t_lst	*lst;
	int		size;
	int		i;
	char	**sc_array;
}	t_cmd;

// lexer
void    ft_loop(char **envp);
t_lst  **get_data_in_lst(char *str);
int  *get_enum_data(char *str);
int		*get_enum_data_loop(int *array, char *str);
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
t_lst	*lst_del_loop(int i, t_lst *lst, int pos, t_lst **s);
t_lst   **get_lst_pos(t_lst **s);
void    del_prev(t_lst *lst, t_lst **s);
int	ft_strlen_v2(const char *str);
void    free_lst(t_lst **s);
void    add_lst(t_lst *lst);

//get quote protos;
void    get_qoute(t_lst **s);
t_lst   *simple_quote(t_lst *lst, t_lst **s);
t_lst   *double_quote(t_lst *lst, t_lst **s);
t_lst   *simple_quote_case_1(t_lst *lst, t_lst **s);
t_lst   *simple_quote_case_2(t_lst *lst, t_lst **s);
t_lst   *simple_quote_case_3(t_lst *lst, t_lst **s);
t_lst   *double_quote_case_1(t_lst *lst, t_lst **s);
t_lst   *double_quote_case_2(t_lst *lst, t_lst **s);
t_lst   *double_quote_case_3(t_lst *lst, t_lst **s);

// get variable protos;
void    get_variable(t_lst **s);
void    translate_variable(t_lst **s, t_env **env);
void    get_variable_case_1(t_lst *lst, t_env *tmp, t_lst **s);
void    get_variable_case_2(t_lst *lst, t_env *env, char *tmp2, int i);
void	loop_get_variable_case_2(t_env *env, t_lst *lst, int i, char *tmp2);
void    get_variable_case_2_loop(t_lst *lst, int i, char *tmp, char *tmp2);
void    get_variable_in_quote(t_lst **s, t_env **envp);
void    get_variable_in_quote_loop(t_lst *lst, t_env **envp);
char    *get_variable_name(t_env **envp, int i, t_lst *lst);
char	*env_name_loop(t_env *env, char *variable);
char	*get_end_variable(t_lst *lst);

//parsing utils
char *ft_strndup(const char *s, int n);
char	*ft_strncpy(char *dst, const char *src, size_t n);
int	ft_strcmp(char *s1, char *s2);


//get command protos;
char	*find_path(char **env);
void	free_tab(char **path_tab);
char	*get_cmd(char **envp, char *cmd);
char	**get_array_execve(t_lst *lst, t_lst **s);
char    **get_array_execve_size_loop(t_lst *lst, int pos, int i, char **array);
char    **get_array_execve_data_loop(int pos, t_lst *lst, char **array, int i);
void	ft_exec_cmd(t_lst *lst, char **envp, char **cmd);
void	ft_exec_cmd_loop(char *tmp, char **cmd, char **envp);
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
int check_pipe_place(t_lst **s);
void    if_only_red(t_lst **s);

// execution.c
void    ft_exec(t_red **s, char **simple_cmd, char **envp, t_env **env);
void    case_1_ft_exec(t_red *red, char **simple_cmd, char **envp, t_exec ex, t_env **env);
void    case_2_ft_exec(t_red *red, char **simple_cmd, char **envp, t_exec ex, t_env **env);
void	loop_case_2_exec(char **envp, t_exec ex, char **simple_cmd, t_red *red, t_env **env);
void    case_3_ft_exec(t_red *red, char **simple_cmd, char **envp, t_exec ex, t_env **env);
void    case_4_ft_exec(t_red *red, char **simple_cmd, char **envp, t_exec ex, t_env **env);
void	loop_case_4_exec(t_exec ex, char **simple_cmd, char **envp, t_red *red, t_env **env);
int	built_in_no_fork(t_env **env, char *simple_cmd, char **array);
int	built_in_a_fork(char *simple_cmd, t_env **env);
void    free_red(t_red **s);
int		check_ambigous_redirect(t_red **s);
void    restore_fd(t_exec ex);

//redirection.c
void    dup_mannager_out(t_red *red, int i, int save_out, char *cmd);
void    red_man_cas_1(t_red *red, int j);
void    red_man_cas_2(t_red *red, int j);
void    red_man_cas_3(t_red *red, int j, int save_out, int i);
void    red_man_cas_4(t_red *red, int j, char *cmd);



#endif