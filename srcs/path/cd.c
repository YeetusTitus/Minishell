/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:20:57 by jforner           #+#    #+#             */
/*   Updated: 2022/04/25 15:27:28 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	free((envname(env, ".", 2))->content);
	(envname(env, ".", 2))->content = getcwd(NULL, 0);
}

// Fr :
// Desc : Fonctionne comme le ecd de bash
// Entrée : Un tableau de chaines de caractères
// Sortie : 1 ou 0 (1 = pas d'erreur, 0 = erreur).
//
// En :
// Desc : Work like the bash's cd (we hope)
// In : A pointer to a the pointert of the environments variables
// Out : 1 or 0 (1 = no error, 0 = error).

int	cd(t_env **env, char *path)
{
	DIR		*dir;
	char	*err;
	int		change;

	change = cd_special(env, &path);
	if (!change)
		return (0);
	dir = opendir(path);
	if (dir == NULL)
	{
		err = ft_strjoin("minishell: cd: ", path);
		perror(err);
		free(err);
		if (change == 1)
			free(path);
		return (0);
	}
	envcwd(env, path);
	if (change == 1)
		free(path);
	closedir(dir);
	return (1);
}
