/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:25:29 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/21 11:22:39 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// mettre les token dans une liste chainee 
t_lst	**get_data_in_lst(char *str)
{
	t_lst	**first;
	t_lex	t;

	t = init_struct(str);
	first = malloc(sizeof(t_lst *));
	*first = t.lst;
	while (t.array[t.i])
		t = big_loop_lexer(t, str);
	free(t.array);
	return (first);
}

t_lex	init_struct(char *str)
{
	t_lex	t;

	t.pos = 1;
	t.start = 0;
	t.i = 0;
	t.array = get_enum_data(str);
	t.lst = ft_calloc(1, sizeof(t_lst));
	return (t);
}

t_lex	loop_get_data_lst(t_lex t, char *str)
{
	t.i++;
	t.lst->data = ft_substr(str, t.start, t.i - t.start);
	t.lst->pos = t.pos++;
	t.lst->next = ft_calloc(1, sizeof(t_lst));
	t.lst->next->prev = t.lst;
	t.lst = t.lst->next;
	t.lst->next = NULL;
	t.start = t.i;
	return (t);
}

t_lex	stop_cond(t_lex t)
{
	t.lst->type = 0;
	t.lst->data = ft_strdup("\0");
	t.lst->next = NULL;
	return (t);
}

t_lex	big_loop_lexer(t_lex t, char *str)
{
	while (t.array[t.i] == t.array[t.i + 1] && (t.array[t.i] == -1
			|| t.array[t.i] == ' '))
		t.i++;
	t.lst->type = t.array[t.i];
	if (t.array[t.i] == '&' && t.array[t.i + 1] == '&' && t.i++ >= 0)
		t.lst->type = '&' * -1;
	else if (t.array[t.i] == '<' && t.array[t.i + 1] == '<' && t.i++ >= 0)
		t.lst->type = '<' * -1;
	else if (t.array[t.i] == '>' && t.array[t.i + 1] == '>' && t.i++ >= 0)
		t.lst->type = '>' * -1;
	if (t.array[t.i] == 0)
		t = stop_cond(t);
	else
		t = loop_get_data_lst(t, str);
	return (t);
}
