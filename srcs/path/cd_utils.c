/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:26:40 by jforner           #+#    #+#             */
/*   Updated: 2022/04/25 18:47:49 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	dircount(t_env **env)
{
	char	**tabstr;
	char	*dot;
	int		nbr;

	dot = ft_strdup(envname(env, ".", 2)->content);
	tabstr = ft_split(dot, '/');
	nbr = tablen(tabstr);
	ft_malloc_error(tabstr, tablen(tabstr));
	free(dot);
	return (nbr + 1);
}

int	checkdir(char *str)
{
	DIR				*dir;
	struct dirent	*d;

	dir = opendir(str);
	d = readdir(dir);
	if (d == NULL)
	{
		closedir(dir);
		return (0);
	}
	closedir(dir);
	return (1);
}

void	cwdisdel(t_env **env)
{
	char			*db;
	int				nb;
	int				i;

	nb = dircount(env);
	while (nb != -1)
	{
		db = ft_strdup("\0");
		i = -1;
		if (nb > 0)
			while (++i < nb)
				db = ft_strjoin_v2(db, "../");
		else
			db = ft_strjoin_v2(db, "./");
		if (!checkdir(db))
			break ;
		free(db);
		nb--;
	}
	if (nb == -1)
		return ;
	db = ft_strjoin_v2(db, "../");
	cd(env, db);
	free(db);
}
