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
	while (q.lst)
	{
		if (q.lst->type == '"')
		{
			q = double_quote(q, s);
			if (q.i > 0)
				return (1);
		}
		else if (q.lst->type == '\'')
		{
			q = simple_quote(q, s);
			if (q.i > 0)
				return (1);
		}
		else
			q.lst = q.lst->next;
	}
	return (0);
}
