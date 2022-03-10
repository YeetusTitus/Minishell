/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:01:18 by jforner           #+#    #+#             */
/*   Updated: 2021/11/10 16:03:35 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfull(const char *s1, const char *s2, char *str)
{
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != 0)
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != 0)
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;

	len = (ft_strlen((char *)s1) + ft_strlen((char *)s2));
	str = malloc(len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	ft_strfull(s1, s2, str);
	str[len] = 0;
	return (str);
}
