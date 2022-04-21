/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:04:32 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/20 15:05:39 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// decouper la chaine de characteres tapee apres le prompt
int	*get_enum_data(char *str)
{
	int	*array;

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
		array[i] = enum_loop(str, i, array);
		i++;
	}
	array[i] = CHAR_NULL;
	return (array);
}

int	enum_loop(char *str, int i, int *array)
{
	if (str[i] == '|')
		array[i] = CHAR_PIPE;
	else if (str[i] == '&')
		array[i] = CHAR_AMPERSAND;
	else if (str[i] == '\'')
		array[i] = CHAR_QOUTE;
	else if (str[i] == '\"')
		array[i] = CHAR_DQUOTE;
	else if (str[i] == ' ')
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
	return (array[i]);
}
