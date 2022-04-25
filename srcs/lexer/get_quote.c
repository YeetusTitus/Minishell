/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:20:14 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/19 17:39:43 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// lire les data entre quote et les enleve si necessaire (ex : '' '')
int	get_qoute(t_lst **s)
{
	t_quote	q;

	q.lst = *s;
	q.i = 0;
	while (q.lst)
	{
		if (q.lst->type == '"')
			q = double_quote(q);
		else if (q.lst->type == '\'')
			q = simple_quote(q);
		else
			q.lst = q.lst->next;
	}
	return (q.i);
}

t_quote	del_quote(t_quote q)
{
	free(q.lst->data);
	q.lst->type = -1;
	q.lst->data = ft_strdup("\0");
	q.lst = q.lst->next;
	return (q);
}

t_quote	simple_quote(t_quote q)
{
	q = del_quote(q);
	while (q.lst->type != '\'')
	{
		if (q.lst->next == NULL && q.lst->type != '\'')
		{
			ft_putstr_fd("Quote error\n", 2);
			q.i = 1;
			return (q);
		}
		q.lst->type = -1;
		q.lst = q.lst->next;
	}
	q = del_quote(q);
	return (q);
}

t_quote	double_quote(t_quote q)
{
	q = del_quote(q);
	while (q.lst->type != '"')
	{
		if (q.lst->type != '$' && q.lst->type != '"')
			q.lst->type = -1;
		if (q.lst->next == NULL && q.lst->type != '"')
		{
			ft_putstr_fd("Quote error\n", 2);
			q.i = 2;
			return (q);
		}
		q.lst = q.lst->next;
	}	
	q = del_quote(q);
	return (q);
}
