/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:30:31 by jforner           #+#    #+#             */
/*   Updated: 2022/03/25 12:58:03 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = -1;
	while (str1[++i] && str2[i])
		if (str1[i] != str2[i])
			return (0);
	if (str1[i] != str2[i])
		return (0);
	return (1);
}
*/
char	**ft_malloc_error(char **tabl, int size)
{
	while (size-- > 0)
		free(tabl[size]);
	free (tabl);
	return (NULL);
}

int	tablen(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i] != NULL)
		i++;
	return (i);
}
