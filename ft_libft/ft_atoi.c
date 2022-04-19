/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 11:00:34 by jforner           #+#    #+#             */
/*   Updated: 2022/04/14 16:36:43 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char_is_numeric(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

int	ft_char_is_operator(char ch)
{
	if (ch == '-' || ch == '+')
		return (1);
	if (ft_char_is_numeric(ch))
		return (1);
	return (0);
}

int	ft_char_is_space(char ch)
{
	if (ch == ' ' || (ch >= 9 && ch <= 13))
		return (1);
	if (ft_char_is_operator(ch))
		return (1);
	return (0);
}

int	ft_while_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		if (!(ft_char_is_space(str[i + 1])))
			return (0);
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int	minus;
	int	answer;
	int	i;

	minus = 0;
	answer = 0;
	i = ft_while_space(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus++;
		i++;
	}
	while (ft_char_is_numeric(str[i]))
	{
		answer *= 10;
		answer += str[i] - 48;
		i++;
	}
	if (minus % 2 == 1)
		answer *= -1;
	return (answer);
}
