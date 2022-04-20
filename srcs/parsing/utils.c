/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:14:23 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/14 17:15:10 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strndup(const char *s, int n)
{
	char	*new;

	new = malloc(sizeof(char) * (n + 1));
	if (new)
	{
		ft_strncpy(new, s, n);
		new[n] = '\0';
	}
	return (new);
}

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

void	free_lst_data(t_lst *lst, t_env *tmp)
{
	free(lst->data);
	lst->data = ft_strdup(tmp->content);
	lst->type = -1;
}
