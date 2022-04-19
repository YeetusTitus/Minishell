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
			{
				ft_putstr_fd("syntax error near unexpected token : ", 2);
				ft_putstr_fd(lst->data, 2);
				ft_putstr_fd("\n", 2);
				return (1);
			}
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

int	check_pipe_place(t_lst **s)
{
	t_lst	*lst;

//	get_lst_pos(s);
	lst = *s;
	while (lst)
	{
		if (lst->pos == 1)
		{
			while (lst->type == ' ')
				lst = lst->next;
			if (lst->type == '|')
			{
				ft_putstr_fd("syntax error near unexpected token : |\n", 1);
				return (1);
			}
		}
		if (lst->type == '|')
		{
			lst = lst->next;
			while (lst->type == ' ')
				lst = lst->next;
			if (lst->type == 0)
			{
				ft_putstr_fd("syntax error near unexpected token : |\n", 1);
				return (1);
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
	t_lst	*lst;
	int		size;
	t_red	**first;
	t_red	*red;

	first = ft_calloc(1, sizeof(t_red));
	red = ft_calloc(1, sizeof(t_red));
	*first = red;
	size = 0;
	lst = *s;
	while (lst)
	{
		if (lst->type == '>' || lst->type == '<' || lst->type == '<' * -1
			|| lst->type == '>' * -1)
			size++;
		else if (lst->type == '|')
		{
			red->type = ft_calloc(1, sizeof(int) * (size + 1));
			red->file = ft_calloc(1, sizeof(char *) * (size + 1));
			size = 0;
			red->next = ft_calloc(1, sizeof(t_red));
			red = red->next;
			red->next = NULL;
		}
		else if (lst->type == 0)
		{
			red->type = ft_calloc(1, sizeof(int) * (size + 1));
			red->file = ft_calloc(1, sizeof (char *) * (size + 1));
			size = 0;
			red->next = NULL;
		}
		lst = lst->next;
	}
	get_red_array_data(s, first);
	return (first);
}

t_red	**get_red_array_data(t_lst **s, t_red **f)
{
	t_lst	*lst;
	t_red	*red;
	int		i;

	lst = *s;
	red = *f;
	i = 0;
	while (lst)
	{
		if (lst->type == '>')
		{
			red->type[i] = lst->type;
			red->file[i] = ft_strdup(&lst->data[1]);
			i++;
			lst = lst->next;
		}
		else if (lst->type == '<')
		{
			red->type[i] = lst->type;
			red->file[i] = ft_strdup(lst->data + 1);
			i++;
			lst = lst->next;
		}
		else if (lst->type == '<' * -1)
		{
			red->type[i] = lst->type;
			red->file[i] = ft_strdup(lst->data + 2);
			i++;
			lst = lst->next;
		}
		else if (lst->type == '>' * -1)
		{
			red->type[i] = lst->type;
			red->file[i] = ft_strdup(lst->data + 2);
			i++;
			lst = lst->next;
		}
		else if (lst->type == '|')
		{
			red->type[i] = -1;
			red->file[i] = NULL;
			i = 0;
			red = red->next;
			lst = lst->next;
		}
		else if (lst->type == 0)
		{
			red->type[i] = -1;
			red->file[i] = NULL;
			red = red->next;
			lst = lst->next;
		}
		else
			lst = lst->next;
	}
	return (f);
}


int	check_red_token(t_lst **s)
{
	t_lst	*lst;

	lst = *s;
	while (lst)
	{
		if (lst->type == '|' || lst->type == '<' || lst->type == '>'
			|| lst->type == '<' * -1 || lst->type == '>' * -1)
		{
			if (lst->next->type == '|' || lst->next->type == '<' || lst->next->type == '>' || lst->next->type == '<' * -1 || lst->next->type == '>' * -1)
			{
				ft_putstr_fd(lst->data, 1);
				ft_putstr_fd(" : syntax error near unexpected token\n", 1);
				return (1);
			}
			if (lst->next->type == 0 || lst->next == NULL)
			{
				ft_putstr_fd(lst->data, 1);
				ft_putstr_fd(" : syntax error near unexpected token\n", 1);
				return (1);
			} 
		}
		lst = lst->next;
	}
	return (0);
}

void	free_red(t_red **s)
{
	t_red   *red;

	if (!s)
		return ;
	while (*s)
	{
		red = (*s)->next;
		if ((*s)->type)
			free((*s)->type);
		if ((*s)->file)
			free((*s)->file);
		free(*s);
		*s = red;
	}
	free(*s);
	free(red);
}


void	if_only_red(t_lst **s)
{
	t_lst   *lst;
	t_lst   *tmp;
	int     secu;

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
			{
				tmp = lst->prev;
				tmp->next = ft_calloc(1, sizeof(t_lst));
				tmp->next->type = -1;
				tmp->next->data = ft_strdup("\0");
				tmp->next->next = lst;
				get_lst_pos(s);
			}
			tmp = lst;
			secu = 0;
		}
		lst = lst->next;
	}
}
