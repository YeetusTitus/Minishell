/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:32:14 by jforner           #+#    #+#             */
/*   Updated: 2022/03/10 14:35:41 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#endif