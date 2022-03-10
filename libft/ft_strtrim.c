/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:34:17 by jforner           #+#    #+#             */
/*   Updated: 2021/10/28 14:57:02 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	unsigned int	len;

	while (ft_isset(*s1, (char *)set) && *s1)
		s1++;
	len = ft_strlen((char *)s1);
	while (len && ft_isset(s1[len - 1], (char *)set))
		len--;
	str = ft_substr((char *)s1, 0, len);
	return (str);
}
