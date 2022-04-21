/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:11:58 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/14 13:13:21 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

void	free_tab(char **path_tab)
{
	int	i;

	if (!path_tab)
		return ;
	i = 0;
	while (path_tab[i])
	{
		free(path_tab[i]);
		i++;
	}
		free(path_tab[i]);
	free(path_tab);
}

char	*get_cmd(char **envp, char *cmd)
{
	char	*path;
	char	**path_tab;
	char	*tmp;
	char	*command;
	int		i;

	path = find_path(envp);
	path_tab = ft_split(path, ':');
	i = 0;
	while (path_tab[i])
	{
		tmp = ft_strjoin(path_tab[i], "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
		{
			free_tab(path_tab);
			return (command);
		}
		free(command);
		i++;
	}
	free_tab(path_tab);
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
		ft_putstr_fd(lst->data, 1);
		ft_putstr_fd(" : command not found\n", 1);
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
		ft_putstr_fd("fork error\n", 1);
		return ;
	}
	if (pid == 0)
		execve(tmp, cmd, envp);
	waitpid(pid, NULL, 0);
	free(tmp);
}
