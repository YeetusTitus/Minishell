/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 10:00:22 by jforner           #+#    #+#             */
/*   Updated: 2021/10/28 13:46:29 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;

	if (size == 0)
		return (ft_strlen((char *)src));
	i = 0;
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < size)
		dest[i] = '\0';
	return (ft_strlen((char *)src));
}
