/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:39:08 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/21 15:00:33 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	c3_ft_exec(t_red *red, char **envp, t_exec ex, t_env **env)
{
	int		pid;

	dup2(ex.save_out, 1);
	close(ex.save_out);
	ex.ret = built_in_no_fork(env, ex.s_cmd[ex.i], ex.s_cmd);
	pid = fork();
	if (pid == 0)
		child_things(ex, red, env, envp);
	else
		close(0);
}

void	c4_ft_exec(t_red *red, char **envp, t_exec ex, t_env **env)
{
	int		pid;
	char	**cmd;

	cmd = NULL;
	pipe(ex.fd);
	dup2(ex.fd[1], 1);
	close(ex.fd[1]);
	ex.ret = built_in_no_fork(env, ex.s_cmd[ex.i], ex.s_cmd);
	pid = fork();
	if (pid == 0)
	{
		close(ex.fd[1]);
		close(ex.fd[0]);
		child_things(ex, red, env, envp);
	}
	else
	{
		close(ex.fd[1]);
		dup2(ex.fd[0], 0);
		close(ex.fd[0]);
		cmd = free_tab(cmd);
	}
}

void	cmd_not_found(char **cmd, t_exec ex)
{
	dup2(ex.save_out, 1);
	close(ex.save_out);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(" : command not found\n", 2);
	cmd = free_tab(cmd);
	exit(127);
}

void	child_things(t_exec ex, t_red *red, t_env **env, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(ex.s_cmd[ex.i], ' ');
	if (cmd && cmd[0] && cmd[0][0] == '/')
		path = ft_strdup(cmd[0]);
	else
		path = get_cmd(envp, cmd[0]);
	if (path && access(path, 0) != 0)
	{
		free(path);
		path = NULL;
	}
	dup_mannager_out(red, 1, ex.save_out, cmd[0]);
	if (ex.ret != -10)
		exit(ex.ret);
	ex.ret = built_in_a_fork(ex.s_cmd[ex.i], env);
	if (ex.ret != -10)
		exit(ex.ret);
	if (!path)
		cmd_not_found(cmd, ex);
	else
		execve(path, cmd, envp);
}
