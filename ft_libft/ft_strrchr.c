/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 6969/07/11 16:33:41 by jforner           #+#    #+#             */
/*   Updated: 2021/10/28 15:34:49 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (str[i])
	{
		if (str[i] == (char)ch)
			j = i;
		i++;
	}
	if (str[i] == (char)ch)
		return ((char *)&str[i]);
	if (j == -1)
		return (NULL);
	return ((char *)&str[j]);
}
