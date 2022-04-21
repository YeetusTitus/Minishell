/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:18:27 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/14 12:19:29 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	dup_mannager_out(t_red *red, int i, int save_out, char *cmd)
{
	int	j;

	j = 0;
	while (red->type[j] != -1)
	{
		if (red->type[j] == '>')
			red_man_cas_1(red, j);
		else if (red->type[j] == '>' * -1)
			red_man_cas_2(red, j);
		else if (red->type[j] == '<')
			red_man_cas_3(red, j, save_out, i);
		else if (red->type[j] == '<' * -1)
			red_man_cas_4(red, j, cmd);
		j++;
	}
}

void	red_man_cas_1(t_red *red, int j)
{
	int	fd;

	fd = open(red->file[j], O_TRUNC | O_CREAT | O_RDWR, 0644);
	dup2(fd, 1);
	close(fd);
}

void	red_man_cas_2(t_red *red, int j)
{
	int	fd;

	fd = open(red->file[j], O_APPEND | O_CREAT | O_RDWR, 0644);
	dup2(fd, 1);
	close(fd);
}

void	red_man_cas_3(t_red *red, int j, int save_out, int i)
{
	int	fd;
	int	save;

	fd = open(red->file[j], O_RDONLY);
	if (fd < 0)
	{
		save = dup(1);
		close(1);
		dup2(save_out, 1);
		close (save_out);
		ft_putstr_fd(red->file[j], 1);
		ft_putstr_fd(" : No such file or directory\n", 1);
		dup2(save, 1);
		close(save);
		if (i == 0)
			return ;
		else
			exit(1);
	}
	dup2(fd, 0);
	close(fd);
}

void	red_man_cas_4(t_red *red, int j, char *cmd)
{
	char	*str;
	int		fdp[2];

	pipe(fdp);
	while (1)
	{
		str = readline("HereDoc > ");
		if (ft_strncmp(str, red->file[j], ft_strlen(red->file[j])) == 0 || !str)
		{
			free(str);
			break ;
		}
		write(fdp[1], str, ft_strlen(str));
		write(fdp[1], "\n", 1);
		free(str);
	}
	close(fdp[1]);
	if (cmd == NULL)
		return ;
	else
	{
		dup2(fdp[0], 0);
		close(fdp[0]);
	}
}
