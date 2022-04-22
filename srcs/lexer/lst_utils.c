/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:23:57 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/22 16:39:28 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	lstsize(t_lst **s)
{
	int		nb;
	t_lst	*lst;

	lst = *s;
	nb = 0;
	while (lst)
	{
		nb++;
		lst = lst->next;
	}
	return (nb);
}

int	lst_del(t_lst **s, int pos)
{
	int		i;
	t_lst	*lst;
	t_lst	*to_del;

	lst = *s;
	i = 0;
	if (lstsize(s) == 0)
		return (-1);
	to_del = lst_del_loop(i, lst, pos, s);
	free(to_del->data);
	free(to_del);
	get_lst_pos(s);
	return (0);
}

t_lst	*lst_del_loop(int i, t_lst *lst, int pos, t_lst **s)
{
	t_lst	*to_del;

	to_del = NULL;
	if (pos == 1)
	{
		to_del = lst;
		lst = lst->next;
		*s = lst;
	}
	else if (pos == lstsize(s))
	{
		while (lst->next)
			lst = lst->next;
		to_del = lst;
		lst->prev->next = NULL;
	}
	else
	{
		while (++i < pos)
			lst = lst->next;
		to_del = lst;
		lst->prev->next = lst->next;
		lst->next->prev = lst->prev;
	}
	return (to_del);
}

t_lst	**get_lst_pos(t_lst **s)
{
	t_lst	*lst;
	int		i;

	if (!s || !*s)
		return (s);
	i = 1;
	lst = *s;
	while (lst)
	{
		lst->pos = i;
		lst = lst->next;
		i++;
	}
	return (s);
}

void	free_lst(t_lst **s)
{
	t_lst	*lst;

	if (!s)
		return ;
	while (*s)
	{
		lst = (*s)->next;
		if ((*s)->data)
			free((*s)->data);
		free(*s);
		*s = lst;
	}
	free(*s);
	free(s);
	free(lst);
	s = NULL;
}
