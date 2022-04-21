/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:42:40 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/21 15:02:03 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_pipe_place(t_lst **s)
{
	t_lst	*lst;

	lst = *s;
	while (lst)
	{
		if (lst->pos == 1)
		{
			while (lst->type == ' ')
				lst = lst->next;
			if (lst->type == '|')
				return (token_error());
		}
		if (lst->type == '|')
		{
			lst = lst->next;
			while (lst->type == ' ')
				lst = lst->next;
			if (lst->type == 0)
				return (token_error());
		}
		lst = lst->next;
	}
	return (0);
}

int	token_error(void)
{
	ft_putstr_fd("syntax error near unexpected token : |\n", 2);
	return (1);
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
			if (lst->next->type == '|' || lst->next->type == '<'
				|| lst->next->type == '>' || lst->next->type == '<' * -1
				|| lst->next->type == '>' * -1)
				return (red_token_error(lst));
			if (lst->next->type == 0 || lst->next == NULL)
				return (red_token_error(lst));
		}
		lst = lst->next;
	}
	return (0);
}

int	red_token_error(t_lst *lst)
{
	ft_putstr_fd(lst->data, 2);
	ft_putstr_fd(" : syntax error near unexpected token\n", 2);
	return (1);
}

int	get_red_in_f_error(t_lst *lst)
{
	ft_putstr_fd("syntax error near unexpected token : ", 2);
	ft_putstr_fd(lst->data, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
