/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:15:12 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/14 12:16:39 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_quote	simple_quote(t_quote q, t_lst **s)
{
	if (q.lst->type == '\'' && q.lst->next->type != '\'')
		q = simple_quote_case_1(q, s);
	else if (q.lst->type == '\'' && q.lst->next->type == '\'')
		q = simple_quote_case_2(q, s);
	return (q);
}

t_quote	simple_quote_case_1(t_quote q, t_lst **s)
{
	q.lst = q.lst->next;
	if (! q.lst || q.lst->type == 0)
	{
		q.i = 1;
		return (q);
	}
	lst_del(s, q.lst->pos - 1);
	while (q.lst)
	{
		if (q.lst->next && q.lst->next->type == '\'')
			break ;
		if (q.lst == NULL || q.lst->next == NULL)
		{
			q.i = 1;
			return (q);
		}
		q.lst->data = ft_strjoin_v2(q.lst->data, q.lst->next->data);
		q.lst->type = -1;
		lst_del(s, q.lst->pos + 1);
	}
	if (q.lst->next->type != 0)
		lst_del(s, q.lst->pos + 1);
	if (q.lst)
		q.lst = q.lst->next;
	return (q);
}

t_quote	simple_quote_case_2(t_quote q, t_lst **s)
{
	q.lst = q.lst->next;
	lst_del(s, q.lst->pos - 1);
	q.lst = q.lst->next;
	lst_del(s, q.lst->pos - 1);
	return (q);
}
