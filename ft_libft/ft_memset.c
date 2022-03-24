/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 13:46:20 by julien            #+#    #+#             */
/*   Updated: 2021/10/28 12:12:17 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, char c, size_t n)
{
	unsigned int	i;
	unsigned char	*v;

	v = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		v[i] = c;
		i++;
	}
	return (v);
}
