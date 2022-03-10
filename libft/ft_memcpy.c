/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 14:03:13 by julien            #+#    #+#             */
/*   Updated: 2021/10/28 12:12:23 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*vd;
	unsigned char	*vs;

	if (n == 0 || (NULL == dest && NULL == src))
		return (dest);
	vd = (unsigned char *)dest;
	vs = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		vd[i] = vs[i];
		i++;
	}
	return (dest);
}
