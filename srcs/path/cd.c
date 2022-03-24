/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:20:57 by jforner           #+#    #+#             */
/*   Updated: 2022/03/24 16:41:40 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
// #include "../../include/minishell.h"

void	cwdisdel(void)
{
	DIR				*dir;
	struct dirent	*d;

	dir = opendir("./");
	d = readdir(dir);
	while (d == NULL)
	{
		chdir("..");
		closedir(dir);
		dir = opendir(".");
		d = readdir(dir);
	}
	closedir(dir);
}

int	cd(t_env **env, char *path)
{
	DIR				*dir;

	if (path == NULL)
	{
		if (envname(env, "HOME") == NULL)
		{
			write(2, "minishell: cd: HOME not set\n", 29);
			return (0);
		}
		path = ft_strdup(envname(env, "HOME")->name);
	}
	dir = opendir(path);
	if (dir == NULL)
	{
		free(path);
		return (0);
	}
	chdir(path);
	export(env, ft_strdup("PWD"), getcwd(NULL, 0));
	free(path);
	return (1);
}
