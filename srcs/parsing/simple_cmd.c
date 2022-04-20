/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:22:40 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/19 19:22:46 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_simple_cmd_array_size(t_lst **s)
{
	t_lst	*lst;
	int		size;

	size = 1;
	lst = *s;
	while (lst)
	{
		if (lst->type == '|')
			size++;
		lst = lst->next;
	}
	return (size);
}

char	**get_simple_cmd_array(t_lst **s)
{
	t_cmd	cmd;

	cmd.lst = *s;
	cmd.size = get_simple_cmd_array_size(s) + 1;
	cmd.sc = malloc(sizeof(char *) * cmd.size);
	cmd.i = 0;
	while (cmd.lst)
	{
		if (cmd.lst->type == -1)
		{
			cmd.sc[cmd.i] = ft_strdup(cmd.lst->data);
			cmd.lst = cmd.lst->next;
			while (cmd.lst->type == -1 || cmd.lst->type == 32)
			{
				cmd.sc[cmd.i] = ft_strjoin_v2(cmd.sc[cmd.i], cmd.lst->data);
				cmd.lst = cmd.lst->next;
			}
			cmd.i++;
		}
		cmd.lst = cmd.lst->next;
	}
	cmd.sc[cmd.i] = NULL;
	return (cmd.sc);
}
