/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:28:03 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/21 20:00:24 by jforner          ###   ########.fr       */
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
	if (ft_strncmp(table[0], "echo", 4) == 0)
	{
		ms_echo(table + 1);
		return (0);
	}
	if (ft_strncmp(table[0], "export", 6) == 0)
		return (export_fork(table, env));
	if (ft_strncmp(table[0], "pwd", 3) == 0)
	{
		i = pwd(env);
		if (i == 0)
			return (1);
		return (0);
	}
	if (ft_strncmp(table[0], "env", 3) == 0)
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
		return (-10);
	if (ft_strncmp(b.table[0], "unset", 5) == 0)
		return (unset_no_fork(b, env));
	if (ft_strncmp(b.table[0], "export", 6) == 0)
		return (export_no_fork(b, env));
	if (ft_strncmp(b.table[0], "cd", 2) == 0)
		return (cd_no_fork(b, env, simple_cmd));
	if (ft_strncmp(b.table[0], "exit", 4) == 0)
	{
		ms_exit(b.table + 1);
		free_tab(b.table);
		return (0);
	}
	free_tab(b.table);
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
				// ft_putstr_fd("name =", 2);
				// ft_putstr_fd(b.name, 2);
				// ft_putstr_fd("! content =", 2);
				// ft_putstr_fd(b.content, 2);
				// ft_putstr_fd("!\n", 2);
				b.ret = export(env, b.name, b.content);
				// if (envname(env, b.name, 0) != NULL)
				// {
				// 	ft_putstr_fd(envname(env, b.name, 0)->name, 2);
				// 	ft_putstr_fd("!\n", 2);
				// }
			}
			else if (!ft_strchr(b.table[b.i], '=') && !(b.j))
			{
				// ft_putstr_fd("name =", 2);
				// ft_putstr_fd(b.table[b.i], 2);
				// ft_putstr_fd("!\n", 2);
				b.ret = export(env, ft_strdup(b.table[b.i]), NULL);
				// if (envname(env, b.name, 1) != NULL)
				// {
				// 	ft_putstr_fd(envname(env, b.name, 1)->name, 2);
				// 	ft_putstr_fd("!\n", 2);
				// }
			}
				b.j++;
		}
			b.j = 0;
			b.i++;
	}
	free_tab(b.table);
	if (b.ret == 1)
		return (0);
	return (1);
}
