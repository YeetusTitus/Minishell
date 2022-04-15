/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:25:29 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/14 17:25:30 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// decouper la chaine de characteres tapee apres le prompt
int  *get_enum_data(char *str)
{
	int *array;

	array = malloc(sizeof(int) * (ft_strlen_v2(str) + 1));
	array = get_enum_data_loop(array, str);
	return (array);
}

int	*get_enum_data_loop(int *array, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			array[i] = CHAR_PIPE;
		else if (str[i] == '&')
			array[i] = CHAR_AMPERSAND;
		else if (str[i] == '\'')
			array[i] = CHAR_QOUTE;
		else if (str[i] == '\"')
			array[i] = CHAR_DQUOTE;
		else  if (str[i] == ' ')
			array[i] = CHAR_WHITESPACE;
		else if (str[i] == '>')
			array[i] = CHAR_GREATER;
		else if (str[i] == '<')
			array[i] = CHAR_LESSER;
		else if (str[i] == '*')
			array[i] = CHAR_WILDCART;
		else if (str[i] == '(')
			array[i] = CHAR_LPARENTHESIS;
		else if (str[i] == ')')
			array[i] = CHAR_RPARENTHESIS;
		else if (str[i] == '$')
			array[i] = CHAR_DOLLAR;
		else
			array[i] = CHAR_GENERAL;
		i++;
	}
	array[i] =  CHAR_NULL;
		return (array);
}

// mettre les token dans une liste chainee 
t_lst  **get_data_in_lst(char *str)
{
	t_lst  *lst;
	t_lst  **first;
	int     *array;
	int     i;
	int     start;
	int     pos;

	pos = 1;
	start = 0;
	i = 0;
	array = get_enum_data(str);
	lst = ft_calloc(1, sizeof(t_lst));
	first = malloc(sizeof(t_lst *));
	*first = lst;
	while(array[i])
	{
		while (array[i] == array[i + 1] && (array[i] == -1 || array[i] == ' '))
			i++;
		lst->type = array[i];
		if (array[i] == '|' && array[i + 1] == '|')
		{
			i++;
			lst->type = '|' * -1;
		}
		else if (array[i] == '&' && array[i + 1] == '&')
		{
			i++;
			lst->type = '&' * -1;
		}
		else if (array[i] == '<' && array[i + 1] == '<')
		{
			i++;
			lst->type = '<' * -1;
		}
		else if (array[i] == '>' && array[i + 1] == '>')
		{
			i++;
			lst->type = '>' * -1;
		}
		if (array[i] == 0)
		{
			lst->type = 0;
			lst->data = ft_strdup("\0");
			lst->next = NULL;
			break ;
		}
		else
		{
			i++;
			lst->data = ft_substr(str, start, i - start);
			lst->pos = pos++;
			lst->next = ft_calloc(1, sizeof(t_lst));
			lst->next->prev = lst;
			lst = lst->next;
			lst->next = NULL;
			start = i;
		}
	}
	free(array);
	return (first);
}
