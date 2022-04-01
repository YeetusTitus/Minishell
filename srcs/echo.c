/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:51:02 by jforner           #+#    #+#             */
/*   Updated: 2022/04/01 17:56:18 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_ch(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != c)
			return (0);
	return (1);
}

int	ms_echo(char **table)
{
	int	i;

	i = -1;
	if (table[0][0] == '-' && is_ch(&table[0][1], 'n'))
	{
		free(table[0]);
		table[0] = ft_strdup("-n");
	}
	while (++i < tablen(table))
	{
		if (!(i == 0 && ft_strcmp(table[i], "-n")))
		{
			write(1, table[i], ft_strlen(table[i]));
			write(1, " ", 1);
		}
	}
	if (table == NULL || !ft_strcmp(table[0], "-n"))
		write(1, "\n", 1);
	return (1);
}
