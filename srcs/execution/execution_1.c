/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:39:08 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/14 13:00:56 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// fonction principale de l execution, tout se passe ici
void	ft_exec(t_red **s, char **simple_cmd, char **envp, t_env **env)
{
	t_exec	ex;
	t_red	*red;

	red = *s;
	ex.i = 0;
	ex.save_out = dup(1);
	ex.save_in = dup(0);
	while (simple_cmd[ex.i])
	{
		if (ex.i == 0 && !simple_cmd[ex.i + 1])
			case_1_ft_exec(red, simple_cmd, envp, ex, env);
		else if (ex.i == 0 && simple_cmd[ex.i])
			case_2_ft_exec(red, simple_cmd, envp, ex, env);
		else if (ex.i > 0 && !simple_cmd[ex.i + 1])
			case_3_ft_exec(red, simple_cmd, envp, ex, env);
		else if (ex.i > 0 && simple_cmd[ex.i + 1])
			case_4_ft_exec(red, simple_cmd, envp, ex, env);
		ex.i++;
		red = red->next;
	}
	restore_fd(ex);
}

void	restore_fd(t_exec ex)
{
	while (wait(NULL) != -1)
		;
	dup2(ex.save_out, 1);
	dup2(ex.save_in, 0);
	close(ex.save_out);
	close(ex.save_in);
}

void	case_1_ft_exec(t_red *red, char **simple_cmd, char **envp, t_exec ex, t_env **env)
{
	char	*path;
	char	**cmd;
	int		pid;
	int		fd;
	int		i;

	cmd = NULL;
	fd = 0;
	ex.ret = built_in_no_fork(env, simple_cmd[ex.i], simple_cmd);
	pid = fork();
	if (pid == 0)
	{
		cmd = ft_split(simple_cmd[ex.i], ' ');
		path = get_cmd(envp, cmd[0]);
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
			exit(1);
		}
		else
			execve(path, cmd, envp);
	}
	free_tab(cmd);
}

void	case_2_ft_exec(t_red *red, char **simple_cmd, char **envp, t_exec ex, t_env **env)
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
		loop_case_2_exec(envp, ex, simple_cmd, red, env);
	else
	{
		dup2(ex.fd[0], 0);
		close(ex.fd[0]);
		close(ex.fd[1]);
		free_tab(cmd);
	}
}

void	loop_case_2_exec(char **envp, t_exec ex, char **simple_cmd, t_red *red, t_env **env)
{
	char	**cmd;
	char	*path;
	int		i;

	cmd = NULL;
	close(ex.fd[1]);
	close(ex.fd[0]);
	cmd = ft_split(simple_cmd[ex.i], ' ');
	path = get_cmd(envp, cmd[0]);
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
		exit(1);
	}
	else
		execve(path, cmd, envp);
}
