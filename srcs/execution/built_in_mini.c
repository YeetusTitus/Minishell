/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:29:23 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/26 15:10:48 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export_fork(char **table, t_env **env)
{
	int	i;

	i = 0;
	if (table[1])
		return (-10);
	else
		i = export(env, NULL, NULL);
	return (i);
}

int	cd_no_fork(t_built b, t_env **env, char *simple_cmd)
{
	b.i = 3;
	while (b.table[0][b.i] == ' ')
		b.i++;
	b.j = cd(env, simple_cmd + b.i);
	free_tab(b.table);
	if (b.j == 1)
		return (0);
	return (1);
}

int	unset_no_fork(t_built b, t_env **env)
{
	while (b.table[b.i])
	{
		if (!b.j)
			b.j = unset(env, b.table[b.i]);
		else
			unset(env, b.table[b.i]);
		b.i ++;
	}
	free_tab(b.table);
	return (b.j);
}
