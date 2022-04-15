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

	fd = 0;
	pid = fork();
	if (pid == 0)
	{
		cmd = ft_split(simple_cmd[ex.i], ' ');
		dup_mannager_out(red, 1, ex.save_out, cmd[0]);
		is_built_in(env, simple_cmd[ex.i]);
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
			execve(path, cmd, envp);
	}
}

void	case_2_ft_exec(t_red *red, char **simple_cmd, char **envp, t_exec ex, t_env **env)
{
	int		pid;

	pipe(ex.fd);
	dup2(ex.fd[1], 1);
	close(ex.fd[1]);
	pid = fork();
	if (pid == 0)
		loop_case_2_exec(envp, red, ex, simple_cmd, env);
	else
	{
		dup2(ex.fd[0], 0);
		close(ex.fd[0]);
		close(ex.fd[1]);
	}
}

void	loop_case_2_exec(char **envp, t_red *red, t_exec ex, char **simple_cmd, t_env **env)
{
	char	**cmd;
	char	*path;

	close(ex.fd[1]);
	close(ex.fd[0]);
	cmd = ft_split(simple_cmd[ex.i], ' ');
	dup_mannager_out(red, 1, ex.save_out, cmd[0]);
	is_built_in(env, simple_cmd[ex.i]);
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
		execve(path, cmd, envp);
}
