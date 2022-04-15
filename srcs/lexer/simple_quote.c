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

t_lst	*simple_quote(t_lst *lst, t_lst **s)
{
	if (lst->type == '\'' && lst->next->type != '\'' && lst->next->type != 0)
		lst = simple_quote_case_1(lst, s);
	else if (lst->type == '\'' && lst->next->type == '\'')
		lst = simple_quote_case_2(lst, s);
	else if (lst->type == '\'')
		lst = simple_quote_case_3(lst, s);
	return (lst);
}

t_lst	*simple_quote_case_1(t_lst *lst, t_lst **s)
{
	lst = lst->next;
	lst_del(s, lst->pos - 1);
	while (lst->next->data)
	{
		if (lst->next->type == '\'')
			break ;
		lst->data = ft_strjoin_v2(lst->data, lst->next->data);
		lst->type = -1;
		lst_del(s, lst->pos + 1);
	}
	if (lst->next->type != 0)
		lst_del(s, lst->pos + 1);
	lst = lst->next;
	return (lst);
}

t_lst	*simple_quote_case_2(t_lst *lst, t_lst **s)
{
	lst = lst->next;
	lst_del(s, lst->pos - 1);
	if (lst->next->type == 0)
	{
		lst_del(s, lst->pos);
		return (lst);
	}
	else
	{
		lst = lst->next;
		lst_del(s, lst->pos - 1);
	}
	return (lst);
}

t_lst	*simple_quote_case_3(t_lst *lst, t_lst **s)
{
	if (lst->next->type == 0)
		lst_del(s, lst->pos);
	else
	{
		lst = lst->next;
		lst_del(s, lst->pos - 1);
	}
	return (lst);
}
