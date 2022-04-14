/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:34:44 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/14 12:34:53 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strlen_v2(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_v2(char *s1, char *s2)
{
	int		i1;
	int		i2;
	char	*str;

	if (!s1)
		return (NULL);
	if (!s2)
		return (s1);
	i1 = ft_strlen_v2(s1);
	i2 = ft_strlen_v2(s2);
	str = malloc(sizeof(char) * (i1 + i2 + 1));
	if (!(str))
		return (NULL);
	i1 = 0;
	i2 = 0;
	while (s1[i1])
	{
		str[i1] = s1[i1];
		i1++;
	}
	while (s2[i2])
		str[i1++] = s2[i2++];
	str[i1] = 0;
	free(s1);
	return (str);
}
