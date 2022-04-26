/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:28:03 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/25 16:03:36 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// separer les builts in 
// cd, export avec arg, unset, exit si dans une pipe d'un cote
// echo, pwd, export sans arg

int	built_in_a_fork(char *simple_cmd, t_env **env)
{
	char	**table;
	int		i;

	table = ft_split(simple_cmd, ' ');
	i = 0;
	if (ft_strcmp(table[0], "echo"))
	{
		ms_echo(table + 1);
		return (0);
	}
	if (ft_strcmp(table[0], "export"))
		return (export_fork(table, env));
	if (ft_strcmp(table[0], "pwd"))
	{
		i = pwd(env);
		if (i == 0)
			return (1);
		return (0);
	}
	if (ft_strcmp(table[0], "env"))
	{
		print_env(*env);
		return (0);
	}
	return (-10);
}

int	built_in_no_fork(t_env **env, char *simple_cmd, char **array)
{
	t_built	b;

	b.ret = 0;
	b.j = 0;
	b.table = ft_split(simple_cmd, ' ');
	b.i = 1;
	if (array[1])
	{
		b.table = free_tab(b.table);
		return (-10);
	}
	if (ft_strcmp(b.table[0], "unset"))
		return (unset_no(b, env));
	if (ft_strcmp(b.table[0], "export") && b.table[1])
		return (export_no(b, env));
	if (ft_strcmp(b.table[0], "cd"))
		return (cd_no(b, simple_cmd, env));
	if (ft_strcmp(b.table[0], "exit"))
		return (exit_no(b));
	b.table = free_tab(b.table);
	return (-10);
}

int	export_no_fork(t_built b, t_env **env)
{
	if (!b.table[1])
		return (-10);
	while (b.table[b.i])
	{
		while (b.table[b.i][b.j])
		{
			if (b.table[b.i][b.j] == '=')
			{
				b.name = ft_strndup(b.table[b.i], b.j);
				b.content = ft_strdup(b.table[b.i] + b.j + 1);
				b.ret = export(env, b.name, b.content);
				break ;
			}
			else if (!ft_strchr(b.table[b.i], '=') && !(b.j))
				b.ret = export(env, ft_strdup(b.table[b.i]), NULL);
			b.j++;
		}
			b.j = 0;
			b.i++;
	}
	b.table = free_tab(b.table);
	if (b.ret == 1)
		return (0);
	return (1);
}
