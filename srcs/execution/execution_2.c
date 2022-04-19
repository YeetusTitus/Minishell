/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:39:08 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/14 13:11:30 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	case_3_ft_exec(t_red *red, char **simple_cmd, char **envp, t_exec ex, t_env **env)
{
	int		pid;
	char	*path;
	char	**cmd;
	int		i;

	dup2(ex.save_out, 1);
	close(ex.save_out);
	ex.ret = built_in_no_fork(env, simple_cmd[ex.i], simple_cmd);
	pid = fork();
	if (pid == 0)
	{
		cmd = ft_split(simple_cmd[ex.i], ' ');
		if (cmd[0][0] == '/')
			path = cmd[0];
		else
			path = get_cmd(envp, cmd[0]);
		if (access(path, 0) != 0)
		{
			free(path);
			path = NULL;
		}
		dup_mannager_out(red, 1, ex.save_out, cmd[0]);
		if (ex.ret != -10)
			exit(0);
		i = built_in_a_fork(simple_cmd[ex.i], env);
		if (i != -10)
			exit(0);
		if (!path)
		{
			dup2(ex.save_out, 1);
			close(ex.save_out);
			ft_putstr_fd(cmd[0], 1);
			ft_putstr_fd(" : command not found\n", 1);
			exit(127);
		}
		else
			execve(path, cmd, envp);
	}
	else
		close(0);
}

void	case_4_ft_exec(t_red *red, char **simple_cmd, char **envp, t_exec ex, t_env **env)
{
	int		pid;
	char	**cmd;

	cmd = NULL;
	pipe(ex.fd);
	dup2(ex.fd[1], 1);
	close(ex.fd[1]);
	ex.ret = built_in_no_fork(env, simple_cmd[ex.i], simple_cmd);
	pid = fork();
	if (pid == 0)
		loop_case_4_exec(ex, simple_cmd, envp, red, env);
	else
	{
		close(ex.fd[1]);
		dup2(ex.fd[0], 0);
		close(ex.fd[0]);
		free_tab(cmd);
	}
}

void	loop_case_4_exec(t_exec ex, char **simple_cmd, char **envp, t_red *red, t_env **env)
{
	char	**cmd;
	char	*path;
	int		i;

	close(ex.fd[1]);
	close(ex.fd[0]);
	cmd = ft_split(simple_cmd[ex.i], ' ');
	if (cmd[0][0] == '/')
			path = cmd[0];
	else
		path = get_cmd(envp, cmd[0]);
	if (access(path, 0) != 0)
	{
		free(path);
		path = NULL;
	}
	dup_mannager_out(red, 1, ex.save_out, cmd[0]);
	if (ex.ret != -10)
		exit(0);
	i = built_in_a_fork(simple_cmd[ex.i], env);
		if (i != -10)
			exit(0);
	if (ex.ret != -10)
		exit(0);
	if (!path)
	{
		dup2(ex.save_out, 1);
		close(ex.save_out);
		ft_putstr_fd(cmd[0], 1);
		ft_putstr_fd(" : command not found\n", 1);
		exit(127);
	}
	else
		execve(path, cmd, envp);
}

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
	{
		if (table[1])
			return (-10);
		else
			i = export(env, NULL, NULL);
		if (i == 0)
			return (1);
		return (0);
	}
	if (ft_strncmp(table[0], "pwd", 3) ==0)
	{
		i = pwd(env);
		if (i == 0)
			return (1);
		return (0);
	}
	return (-10);
}

int	built_in_no_fork(t_env **env, char *simple_cmd, char **array)
{
	char	*name;
	char	*content;
	char	**table;
	int		i;
	int		j;
	int		ret;

	ret = 0;
	j = 0;
	table = ft_split(simple_cmd, ' ');
	i = 1;
	if (array[1])
		return (-10);
	if (ft_strncmp(table[0], "unset", 5) == 0)
	{
		while (table[i++])
			j = unset(env, table[i]);    // voir le ret d erreur pour unset si content = NULL
		if (j == 1)
			return (0);
		else
			return (1);
	}
	if (ft_strncmp(table[0], "export", 6) == 0)
	{
		if (!table[1])
			return (-10);
		while (table[i])
		{
			while (table[i][j++])
			{
				if (table[i][j] == '=')
				{
					name = ft_strndup(table[i], j);
					content = ft_strdup(table[i] + j + 1);
					printf("name == %s  -  content == %s\n", name , content);
					ret = export(env, name, content);
				}
				else if (table[i][j + 1] == '\0' && table[i][j] != '=')
					ret = export(env, table[i], NULL);
			}
				j = 0;
				i++;
			}
		if (ret == 1)
			return (0);
		else
			return (1);
	}
	if (ft_strncmp(table[0], "cd", 2) ==0)
	{
		i = 3;
		while (table[0][i] == ' ')
			i++;
		j = cd(env, simple_cmd + i);
		if (j == 1)
			return (0);
		else
			return (1);
	}
	if (ft_strncmp(table[0], "exit", 4) ==0)
	{
		ms_exit(table + 1, env);
		return (0);
	}
	return (-10);
}