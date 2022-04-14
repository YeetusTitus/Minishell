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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (ft_strlen_v2(s1) != ft_strlen_v2(s2))
		return (1);
	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
