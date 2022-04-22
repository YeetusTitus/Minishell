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
void	get_qoute(t_lst **s)
{
	t_lst	*lst;

	lst = *s;
	while (lst)
	{
		if ((lst->type == '\'' || lst ->type == '"') && lst->next->type == 0)
		{
			lst_del(s, lst->pos);
			break ;
		}
		if (lst->type == '"')
			lst = double_quote(lst, s);
		else if (lst->type == '\'')
			lst = simple_quote(lst, s);
		else
			lst = lst->next;
	}
}
