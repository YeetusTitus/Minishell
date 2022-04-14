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

	dup2(ex.save_out, 1);
	close(ex.save_out);
	pid = fork();
	if (pid == 0)
	{
		cmd = ft_split(simple_cmd[ex.i], ' ');
		dup_mannager_out(red, 1, ex.save_out, cmd[0]);
		path = get_cmd(envp, cmd[0]);
		if (!path)
		{
			dup2(ex.save_out, 1);
			close(ex.save_out);
			ft_putstr_fd(cmd[0], 1);
			ft_putstr_fd(" : command not found\n", 1);
			exit(1);
		}
		else
			exec_or_built_in(cmd, path, envp, env);
	}
	else
		close(0);
}

void	case_4_ft_exec(t_red *red, char **simple_cmd, char **envp, t_exec ex, t_env **env)
{
	int		pid;

	pipe(ex.fd);
	dup2(ex.fd[1], 1);
	close(ex.fd[1]);
	pid = fork();
	if (pid == 0)
		loop_case_4_exec(ex, red, simple_cmd, envp, env);
	else
	{
		close(ex.fd[1]);
		dup2(ex.fd[0], 0);
		close(ex.fd[0]);
	}
}

void	loop_case_4_exec(t_exec ex, t_red *red, char **simple_cmd, char **envp, t_env **env)
{
	char	**cmd;
	char	*path;

	close(ex.fd[1]);
	close(ex.fd[0]);
	cmd = ft_split(simple_cmd[ex.i], ' ');
	dup_mannager_out(red, 1, ex.save_out, cmd[0]);
	path = get_cmd(envp, cmd[0]);
	if (!path)
	{
		dup2(ex.save_out, 1);
		close(ex.save_out);
		ft_putstr_fd(cmd[0], 1);
		ft_putstr_fd(" : command not found\n", 1);
		exit(1);
	}
	else
		exec_or_built_in(cmd, path, envp, env);
}

void	exec_or_built_in(char **cmd, char *path, char **envp, t_env **env)
{

	printf("cmd == %s\n", cmd[0]);

	char	*content;
	int		i;

	i = 1;
	if (ft_strcmp(cmd[0], "echo") ==0)
	{
		ms_echo(cmd);
		exit(0);
	}
	if (ft_strcmp(cmd[0], "unset") ==0)
	{
		content = ft_strdup(cmd[0]);
		while (cmd[i])
		{
			ft_strjoin_v2(content, " ");
			ft_strjoin_v2(content, cmd[i]);
			i++;
		}
		unset(env, content);
		exit(0);
	}
	if (ft_strcmp(cmd[0], "export") ==0)
	{
		content = ft_strdup(cmd[0]);
		while (cmd[i])
		{
			ft_strjoin_v2(content, " ");
			ft_strjoin_v2(content, cmd[i]);
			i++;
		}
		free(cmd);
		cmd = ft_split(content, '=');
		i = 0;
		if (!cmd || cmd[0][0] == '\0')
			export(env, NULL, NULL);
		else
		{
			while(cmd[i])
			{
				if (cmd[i + 1] == NULL)
					break ;
				export(env, cmd[i], cmd[i + 1]);
			}
		}
		exit(0);
	}
	if (ft_strcmp(cmd[0], "cd") ==0)
	{
		content = ft_strdup(cmd[0]);
		while (cmd[i])
		{
			ft_strjoin_v2(content, " ");
			ft_strjoin_v2(content, cmd[i]);
			i++;
		}
		cd(env, content);
		exit(0);
	}
	if (ft_strcmp(cmd[0], "pwd") ==0)
	{
		pwd(env);
		exit(0);
	}
	if (ft_strcmp(cmd[0], "exit") ==0)
	{
		ms_exit(cmd, env);
		exit(0);
	}
	else
		execve(path, cmd, envp);
}