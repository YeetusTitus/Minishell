/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_n_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:19:19 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/14 17:25:15 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// init le tableau de simple cmd et le tableau de redirection associe;

int	get_redirection_with_file(t_lst **s)
{
	t_lst	*lst;

	lst = *s;
	while (lst)
	{
		if (lst->type == '<' || lst->type == '>' || lst->type == '<' * -1
			|| lst->type == '>' * -1)
		{
			while (lst->next->type == 32 && lst->next)
				lst_del(s, lst->pos + 1);
			if (!lst->next || lst->next->type != -1)
				return (get_red_in_f_error(lst));
			else
			{
				lst->data = ft_strjoin_v2(lst->data, lst->next->data);
				lst_del(s, lst->pos + 1);
			}
		}
		lst = lst->next;
	}
	return (0);
}

int	get_nb_red_lst(t_lst **s)
{
	t_lst	*lst;
	int		nb;

	lst = *s;
	nb = 1;
	while (lst)
	{
		if (lst->type == '|')
			nb++;
	}
	return (nb);
}

t_red	**get_red_array(t_lst **s)
{
	t_pars	p;
	t_red	**first;

	first = ft_calloc(1, sizeof(t_red));
	p.red = ft_calloc(1, sizeof(t_red));
	*first = p.red;
	p.size = 0;
	p.lst = *s;
	while (p.lst)
	{
		if (p.lst->type == '>' || p.lst->type == '<' || p.lst->type == '<' * -1
			|| p.lst->type == '>' * -1)
			p.size++;
		else if (p.lst->type == '|')
			p = get_red_array_loop(p);
		else if (p.lst->type == 0)
			p = get_red_array_loop_2(p);
		p.lst = p.lst->next;
	}
	get_red_array_data(s, first);
	return (first);
}

t_pars	get_red_array_loop(t_pars p)
{
	p.red->type = ft_calloc(1, sizeof(int) * (p.size + 1));
	p.red->file = ft_calloc(1, sizeof(char *) * (p.size + 1));
	p.size = 0;
	p.red->next = ft_calloc(1, sizeof(t_red));
	p.red = p.red->next;
	p.red->next = NULL;
	return (p);
}

t_pars	get_red_array_loop_2(t_pars p)
{
	p.red->type = ft_calloc(1, sizeof(int) * (p.size + 1));
	p.red->file = ft_calloc(1, sizeof (char *) * (p.size + 1));
	p.size = 0;
	p.red->next = NULL;
	return (p);
}
