/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:11:58 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/21 15:01:19 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_path(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] && ft_strncmp("PATH", env[i], 4))
		i++;
	if (env[i] && ft_strlen_v2(env[i]) >= 5)
		return (env[i] + 5);
	else
		return (NULL);
}

char	**free_tab(char **path_tab)
{
	int	i;

	if (!path_tab)
		return (NULL);
	i = 0;
	while (path_tab[i])
	{
		free(path_tab[i]);
		i++;
	}
	free(path_tab[i]);
	free(path_tab);
	return (NULL);
}

char	*get_cmd(char **envp, char *cmd)
{
	t_g_cmd	c;

	c.path = find_path(envp);
	if (c.path)
		c.path_tab = ft_split(c.path, ':');
	else
		return (NULL);
	c.i = 0;
	while (c.path_tab[c.i])
	{
		c.tmp = ft_strjoin(c.path_tab[c.i], "/");
		c.command = ft_strjoin(c.tmp, cmd);
		free(c.tmp);
		if (access(c.command, 0) == 0)
		{
			free_tab(c.path_tab);
			return (c.command);
		}
		free(c.command);
		c.i++;
	}
	free_tab(c.path_tab);
	return (NULL);
}

void	ft_exec_cmd(t_lst *lst, char **envp, char **cmd)
{
	char	*tmp;

	if (cmd == NULL || !lst)
		return ;
	while (lst->type == 32 && lst->next && lst)
		lst = lst->next;
	tmp = get_cmd(envp, lst->data);
	if (!tmp)
	{
		ft_putstr_fd(lst->data, 2);
		ft_putstr_fd(" : command not found\n", 2);
		return ;
	}
	else
		ft_exec_cmd_loop(tmp, cmd, envp);
}

void	ft_exec_cmd_loop(char *tmp, char **cmd, char **envp)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork error\n", 2);
		return ;
	}
	if (pid == 0)
		execve(tmp, cmd, envp);
	waitpid(pid, NULL, 0);
	free(tmp);
}
