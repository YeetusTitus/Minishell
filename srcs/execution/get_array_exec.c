/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_array_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:06:05 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/14 14:06:32 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_array_execve(t_lst *lst, t_lst **s)
{
	char	**array;
	int		i;
	int		pos;

	pos = 0;
	array = NULL;
	i = 0;
	if (!lst || !s)
	{
		array = NULL;
		return (array);
	}
	array = g_a_execve_size(lst, pos, i, array);
	lst = *s;
	if (array)
		array = g_a_execve_data(pos, lst, array, i);
	return (array);
}

char	**g_a_execve_size(t_lst *lst, int pos, int i, char **array)
{
	while (lst->type == 32 && lst->next)
		lst = lst->next;
	if (lst->type != -1)
		return (NULL);
	pos = lst->pos;
	while (lst->type == -1 || lst->type == 32)
	{
		if (lst->type == -1)
			i++;
		lst = lst->next;
	}
	array = malloc(sizeof(char *) * (i + 1));
	return (array);
}

char	**g_a_execve_data(int pos, t_lst *lst, char **array, int i)
{
	int	j;

	j = 0;
	while (lst->pos != pos)
		lst = lst->next;
	while (j < i)
	{
		if (lst->type == -1)
		{
			array[j] = ft_strdup(lst->data);
			j++;
		}
		lst = lst->next;
	}
	array[j] = NULL;
	return (array);
}
