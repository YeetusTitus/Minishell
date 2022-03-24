/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:24:49 by jforner           #+#    #+#             */
/*   Updated: 2021/10/28 19:41:04 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;
	int		len;

	i = -1;
	len = ft_strlen((char *)s);
	str = (char *) malloc(len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (s[++i] != 0)
	{
		str[i] = f(i, s[i]);
	}
	str[i] = 0;
	return (str);
}
