/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 18:05:35 by jforner           #+#    #+#             */
/*   Updated: 2021/10/28 12:11:44 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	count;
	unsigned int	i;

	count = 0;
	while (dest[count] != '\0' && count < size)
		count++;
	i = count;
	while (src[i - count] != '\0' && i < size - 1)
	{
		if (count < size)
			dest[i] = src[i - count];
		i++;
	}
	if (count < size)
		dest[i] = '\0';
	return (count + ft_strlen((char *)src));
}
