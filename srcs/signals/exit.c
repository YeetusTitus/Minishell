/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:33:45 by jforner           #+#    #+#             */
/*   Updated: 2022/04/01 17:54:46 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

unsigned char	ms_atouc(char *str)
{
	int				i;
	unsigned char	nbr;

	i = -1;
	nbr = 0;
	while (++i < ft_strlen(str))
	{
		nbr *= 10;
		if (str[i] >= '0' && str[i] <= '9')
			nbr += (str[i] - '0');
	}
	if (str[0] == '-')
		nbr *= (-1);
	return (nbr);
}

int	verif_maxlong2(char *nbr, int neg)
{
	int			i;
	long long	maxi;
	long long	temp;

	i = -1;
	maxi = 0;
	temp = 0;
	while (nbr[++i])
	{
		temp = maxi;
		maxi *= 10;
		if (neg)
		{
			maxi -= (nbr[i] - '0');
			if (maxi > temp)
				return (0);
		}
		else
		{
			maxi += (nbr[i] - '0');
			if (maxi < temp)
				return (0);
		}
	}
	return (1);
}

int	verif_maxlong(char *nbr)
{
	size_t	i;
	int		neg;

	i = 0;
	neg = 0;
	if (nbr[0] == '-')
		neg++;
	while (nbr[i] == '0' || nbr[i] == '-')
		i++;
	if (ft_strlen(&nbr[i]) > 19)
		return (0);
	if (!verif_maxlong2(&nbr[i], neg))
		return (0);
	return (1);
}

int	verif_isdigit(char *str)
{
	int	j;

	j = -1;
	while (str[++j])
	{
		if ((str[0] < '0' || str[0] > '9') && str[0] != '-')
			return (0);
		if ((str[j] < '0' || str[j] > '9') && j > 0)
			return (0);
	}
	return (1);
}

int	ms_exit(char **table)
{
	printf("exit\n");
	if (verif_isdigit(*table) || !verif_maxlong(*table))
	{
		write(2, "minishell: exit: ", 15);
		write(2, *table, ft_strlen(*table));
		write(2, ": numeric argument required\n", 28);
		return (-1);
	}
	if (tablen(table) > 1)
	{
		write(2, "minishell: exit: too many arguments\n", 35);
		return (-2);
	}
	return (ms_atouc(*table));
}
