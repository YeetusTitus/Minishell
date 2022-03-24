/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:43:45 by julien            #+#    #+#             */
/*   Updated: 2021/10/28 16:37:39 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*v;

	v = (unsigned char *)str;
	i = 0;
	while (v[i] != (unsigned char)c && i < n)
		i++;
	if (i == n)
		return (NULL);
	return ((void *)&v[i]);
}
