/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:20:57 by jforner           #+#    #+#             */
/*   Updated: 2022/03/31 19:46:04 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
// #include "../../include/minishell.h"

void	envoldpwd2(t_env **env)
{
	if (!env_exist(env, "OLDPWD"))
		envadd_back(&env[2], envnew(ft_strdup("OLDPWD"),
				ft_strdup((envname(env, "PWD", 2))->content)));
	else
	{
		if (envname(env, "PWD", 2) == NULL)
			envadd_back(&env[2], envnew(ft_strdup("PWD"), getcwd(NULL, 0)));
		if (envname(env, "OLDPWD", 2) == NULL)
			envadd_back(&env[2], envnew(ft_strdup("OLDPWD"),
					ft_strdup((envname(env, "PWD", 2))->content)));
		else
		{
			free((envname(env, "OLDPWD", 2))->content);
			(envname(env, "OLDPWD", 2))->content =
			ft_strdup((envname(env, "PWD", 2))->content);
		}
		if (envname(env, "OLDPWD", 1) != NULL
			|| envname(env, "OLDPWD", 0) != NULL)
			export(env, ft_strdup("OLDPWD"),
				ft_strdup((envname(env, "PWD", 2))->content));
	}
}

void	envoldpwd(t_env **env)
{
	int	i;

	i = -1;
	if (!env_exist(env, "PWD") || envname(env, "PWD", 1) != NULL)
	{
		if (!env_exist(env, "OLDPWD"))
			envadd_back(&env[2], envnew(ft_strdup("OLDPWD"), ft_strdup("")));
		while (++i < 3)
		{
			if (envname(env, "OLDPWD", i) != NULL)
			{
				if ((envname(env, "OLDPWD", i))->content != NULL)
					free((envname(env, "OLDPWD", i))->content);
				(envname(env, "OLDPWD", i))->content = ft_strdup("");
			}
		}
	}
	else
		envoldpwd2(env);
}

void	envcwd(t_env **env, char *path)
{
	envoldpwd(env);
	chdir(path);
	if (!env_exist(env, "PWD"))
		envadd_back(&env[2], envnew(ft_strdup("PWD"), getcwd(NULL, 0)));
	else
	{
		free((envname(env, "PWD", 2))->content);
		(envname(env, "PWD", 2))->content = getcwd(NULL, 0);
		if (envname(env, "PWD", 0) != NULL || envname(env, "PWD", 1) != NULL)
		{
			export(env, ft_strdup("PWD"), getcwd(NULL, 0));
		}
	}
	free((envname(env, "CWD", 2))->content);
	(envname(env, "CWD", 2))->content = getcwd(NULL, 0);
}

void	cwdisdel(t_env **env)
{
	DIR				*dir;
	struct dirent	*d;

	dir = opendir("./");
	d = readdir(dir);
	while (d == NULL)
	{
		cd(env, ft_strdup(".."));
		closedir(dir);
		dir = opendir(".");
		d = readdir(dir);
	}
	closedir(dir);
}

int	cd(t_env **env, char *path)
{
	DIR		*dir;
	char	*err;

	if (path == NULL)
	{
		if (envname(env, "HOME", 0) == NULL)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (0);
		}
		path = ft_strdup(envname(env, "HOME", 0)->content);
	}
	dir = opendir(path);
	if (dir == NULL)
	{
		err = ft_strjoin("minishell: cd: ", path);
		perror(err);
		free(err);
		free(path);
		return (0);
	}
	envcwd(env, path);
	free(path);
	closedir(dir);
	return (1);
}
