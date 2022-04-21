/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_array_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:13:09 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/20 16:13:46 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_red	**get_red_array_data(t_lst **s, t_red **f)
{
	t_data	d;

	d.lst = *s;
	d.red = *f;
	d.i = 0;
	while (d.lst)
	{
		if (d.lst->type == '>')
			d = get_red_array_data_thing(d, 1);
		else if (d.lst->type == '<')
			d = get_red_array_data_thing(d, 1);
		else if (d.lst->type == '<' * -1)
			d = get_red_array_data_thing(d, 2);
		else if (d.lst->type == '>' * -1)
			d = get_red_array_data_thing(d, 2);
		else if (d.lst->type == '|')
			d = get_red_array_data_thing_pipe(d);
		else if (d.lst->type == 0)
			d = get_red_array_data_thing_end(d);
		else
			d.lst = d.lst->next;
	}
	return (f);
}

t_data	get_red_array_data_thing(t_data d, int i)
{
	d.red->type[d.i] = d.lst->type;
	d.red->file[d.i] = ft_strdup(d.lst->data + i);
	d.i++;
	d.lst = d.lst->next;
	return (d);
}

t_data	get_red_array_data_thing_pipe(t_data d)
{
	d.red->type[d.i] = -1;
	d.red->file[d.i] = NULL;
	d.i = 0;
	d.red = d.red->next;
	d.lst = d.lst->next;
	return (d);
}

t_data	get_red_array_data_thing_end(t_data d)
{
	d.red->type[d.i] = -1;
	d.red->file[d.i] = NULL;
	d.red = d.red->next;
	d.lst = d.lst->next;
	return (d);
}
