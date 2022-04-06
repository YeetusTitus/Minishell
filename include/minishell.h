/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:32:14 by jforner           #+#    #+#             */
/*   Updated: 2022/04/06 13:32:53 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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
# include <errno.h>

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

// env/envutils
t_env	*envnew(char *name, char *content);
int		envsize(t_env *lst);
t_env	*envlast(t_env *lst);
void	envadd_back(t_env **alst, t_env *new);
void	envadd_front(t_env **alst, t_env *new);

// env/envutils2
t_env	*envname(t_env **env, char *name, int colonne);
void	free_env(t_env *env);
void	free_export(t_env **env);

// env/createenv
int		lenachr(char *str, char chr);
int		lenbchr(char *str, char chr);
char	**content_env(char **cont, char *line);
void	create_env2(t_env **env);
int		create_env(t_env **env, char **envp);

// env/export
int		env_exist(t_env **env, char *name);
int		export(t_env **env, char *name, char *content);
int		export_env(t_env **env, char *name, char *content);
void	print_env(t_env *env);
void	print_export(t_env **env);

// env/unset
int		unset(t_env **env, char *name);
int		unset_export(t_env **env, char *name);
int		unset_env_set(t_env **env, char *name, int column);

// utils/utils1
int		ft_strcmp(char *str1, char *str2);
char	**ft_malloc_error(char **tabl, int size);
int		tablen(char **tabl);

// path/cd
int		cd(t_env **env, char *path);
void	cwdisdel(t_env **env);
void	envcwd(t_env **env, char *path);
void	envoldpwd(t_env **env);
void	envoldpwd2(t_env **env);

// path/pwd
int		pwd(t_env **env);
// echo
void	ms_echo(char **table);
#endif