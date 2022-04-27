/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:28:03 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/27 11:20:32 by jforner          ###   ########.fr       */
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
	if (ft_strcmp(table[0], "export") && !table[1])
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
		free_tab(b.table);
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
				b = export_no_fork_loop(b, env);
				break ;
			}
			else if (!ft_strchr(b.table[b.i], '=') && !(b.j))
			{
				if (!b.ret)
					b.ret = export(env, ft_strdup(b.table[b.i]), NULL);
				else
					export(env, ft_strdup(b.table[b.i]), NULL);
			}
			b.j++;
		}
			b.j = 0;
			b.i++;
	}
	b.table = free_tab(b.table);
	return (b.ret);
}

int	export_error(t_built b)
{
	ft_putstr_fd("export : =", 2);
	ft_putstr_fd(b.content, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	b.ret = 1;
	free(b.name);
	free(b.content);
	return (b.ret);
}

t_built	export_no_fork_loop(t_built b, t_env **env)
{
	b.name = ft_strndup(b.table[b.i], b.j);
	b.content = ft_strdup(b.table[b.i] + b.j + 1);
	if (!b.name || b.name[0] == '\0')
		b.ret = export_error(b);
	else if (!b.ret)
		b.ret = export(env, b.name, b.content);
	else
		export(env, b.name, b.content);
	return (b);
}
