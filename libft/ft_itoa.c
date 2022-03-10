/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:46:24 by jforner           #+#    #+#             */
/*   Updated: 2021/10/28 12:12:31 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(int n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_intstr(int n, char *str, int len, int spe)
{
	str[len] = 0;
	if (spe == 1)
		str[--len] = 8 + 48;
	if (spe >= 0)
		str[0] = '-';
	while (n >= 10)
	{
		len--;
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	str[len - 1] = n + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	int		special;
	char	*str;

	special = -1;
	if (n == -2147483648)
	{
		n /= 10;
		special++;
	}
	len = ft_intlen(n);
	if (n < 0)
	{
		special++;
		n *= -1;
		len = ft_intlen(n) + 1 + special;
	}
	str = malloc(len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	str = ft_intstr(n, str, len, special);
	return (str);
}
