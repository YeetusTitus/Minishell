/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 12:21:26 by julien            #+#    #+#             */
/*   Updated: 2021/10/28 12:12:20 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*vd;
	unsigned char	*vs;

	if (n == 0 || (dest <= 0 && src <= 0))
		return (dest);
	vd = (unsigned char *)dest;
	vs = (unsigned char *)src;
	i = 0;
	if (vd > vs)
	{
		while (n-- > 0)
			vd[n] = vs[n];
	}
	else
	{
		while (i < n)
		{
			vd[i] = vs[i];
			i++;
		}
	}
	return (dest);
}
