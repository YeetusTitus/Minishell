/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:03:12 by jforner           #+#    #+#             */
/*   Updated: 2021/10/28 12:12:26 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	count;
	unsigned char	*v1;
	unsigned char	*v2;
	int				brk;

	count = 0;
	brk = 0;
	v1 = (unsigned char *)s1;
	v2 = (unsigned char *)s2;
	if (!n)
		return (0);
	while (count < n)
	{
		if (v1[count] != v2[count])
		{
			brk = 1;
			break ;
		}
		count++;
	}
	if (brk == 1)
		return (v1[count] - v2[count]);
	return (v1[count - 1] - v2[count - 1]);
}
