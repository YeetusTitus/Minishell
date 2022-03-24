/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:32:58 by jforner           #+#    #+#             */
/*   Updated: 2021/11/02 14:21:21 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrn(const char *str, const char *find, size_t n)
{
	size_t	i;

	i = 0;
	while (str[i] == find[i] && find[i] && i < n && str[i])
		i++;
	if (str[i - 1] == find[i - 1] && !find[i])
		return (1);
	return (0);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t size)
{
	unsigned int	i;

	if (!ft_strlen(to_find))
		return ((char *)str);
	i = 0;
	while (str[i] != '\0' && i <= size)
	{
		if (ft_strrn(&str[i], to_find, size - i))
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
