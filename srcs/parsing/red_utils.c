/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:19:01 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/22 16:39:40 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_red(t_red **s)
{
	t_red	*red;

	if (!s)
		return ;
	while (*s)
	{
		red = (*s)->next;
		if ((*s)->type)
			free((*s)->type);
		if ((*s)->file)
			free_tab((*s)->file);
		free(*s);
		*s = red;
	}
	free(*s);
	free(s);
	free(red);
}

void	if_only_red(t_lst **s)
{
	t_lst	*lst;
	t_lst	*tmp;
	int		secu;

	lst = *s;
	tmp = lst;
	secu = 0;
	while (lst)
	{
		if (lst->type == '|')
		{
			while (tmp->pos != lst->pos)
			{
				if (tmp->type == -1)
					secu++;
				tmp = tmp->next;
			}
			if (secu == 0)
				if_only_red_loop(tmp, lst, s);
			tmp = lst;
			secu = 0;
		}
		lst = lst->next;
	}
}

void	if_only_red_loop(t_lst *tmp, t_lst *lst, t_lst **s)
{
	tmp = lst->prev;
	tmp->next = ft_calloc(1, sizeof(t_lst));
	tmp->next->type = -1;
	tmp->next->data = ft_strdup("\0");
	tmp->next->next = lst;
	get_lst_pos(s);
}
