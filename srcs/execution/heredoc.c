/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:45:47 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/27 15:46:51 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	red_man_cas_4(t_red *red, int j, char *cmd, t_env **env)
{
	t_hd	hd;

	pipe(hd.fdp);
	while (1)
	{
		hd = hd_init(env);
		hd = get_hd_variable(hd);
		if (ft_strcmp(hd.str, red->file[j]) || !hd.str)
		{
			free(hd.str);
			break ;
		}
		write(hd.fdp[1], hd.str, ft_strlen(hd.str));
		write(hd.fdp[1], "\n", 1);
	}
	close(hd.fdp[1]);
	if (cmd == NULL)
		return ;
	else
	{
		dup2(hd.fdp[0], 0);
		close(hd.fdp[0]);
	}
}

t_hd	hd_init(t_env **env)
{
	t_hd	hd;

	hd.str = readline("HereDoc > ");
	hd.s = get_data_in_lst(hd.str);
	free(hd.str);
	hd.str = NULL;
	get_variable(hd.s);
	translate_variable(hd.s, env);
	return (hd);
}

t_hd	get_hd_variable(t_hd hd)
{
	while (*hd.s)
	{
		if (!hd.str)
			hd.str = ft_strdup((*hd.s)->data);
		else
			hd.str = ft_strjoin_v2(hd.str, (*hd.s)->data);
		*hd.s = (*hd.s)->next;
	}
	return (hd);
}
