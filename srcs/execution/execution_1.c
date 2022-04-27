/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:39:08 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/21 18:30:01 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// fonction principale de l execution, tout se passe ici
void	ft_exec(t_red **s, char **simple_cmd, char **envp, t_env **env)
{
	t_exec	ex;
	t_red	*red;

	red = *s;
	ex = init_exec(simple_cmd);
	sign_onoff(1);
	while (simple_cmd[ex.i])
	{
		if (ex.i == 0 && !simple_cmd[ex.i + 1])
			ex.pid = c1_ft_exec(red, envp, ex, env);
		else if (ex.i == 0 && simple_cmd[ex.i])
			c2_ft_exec(red, envp, ex, env);
		else if (ex.i > 0 && !simple_cmd[ex.i + 1])
			c3_ft_exec(red, envp, ex, env);
		else if (ex.i > 0 && simple_cmd[ex.i + 1])
			c4_ft_exec(red, envp, ex, env);
		ex.i++;
		red = red->next;
		g_glob.retour = ex.ret;
	}
	restore_fd(ex);
	sign_onoff(0);
}

t_exec	init_exec(char **simple_cmd)
{
	t_exec	ex;

	ex.i = 0;
	ex.ret = -10;
	ex.save_out = dup(1);
	ex.save_in = dup(0);
	ex.s_cmd = simple_cmd;
	return (ex);
}

int	restore_fd(t_exec ex)
{
	while (wait(&ex.pid) != -1)
		;
	if (g_glob.retour == -10)
		g_glob.retour = WEXITSTATUS(ex.pid);
	dup2(ex.save_out, 1);
	dup2(ex.save_in, 0);
	close(ex.save_out);
	close(ex.save_in);
	ex.s_cmd = free_tab(ex.s_cmd);
	return (g_glob.retour);
}

int	c1_ft_exec(t_red *red, char **envp, t_exec ex, t_env **env)
{
	ex.ret = built_in_no_fork(env, ex.s_cmd[ex.i], ex.s_cmd);
	ex.pid = fork();
	if (ex.pid == 0)
		child_things(ex, red, env, envp);
	return (ex.pid);
}

void	c2_ft_exec(t_red *red, char **envp, t_exec ex, t_env **env)
{
	int		pid;

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
		dup2(ex.fd[0], 0);
		close(ex.fd[0]);
		close(ex.fd[1]);
	}
}
