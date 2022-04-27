/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:51:02 by jforner           #+#    #+#             */
/*   Updated: 2022/04/05 18:22:48 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Fr :
// Desc : Vérifie si il n'y a qu'un type de caractère
// dans la chaine de caractères
// Entrée : Une chaine de caractères et le caractère à vérifier
// Sortie : 1 ou 0 (1 = vrai, 0 = faux).
//
// En :
// Desc : Check if there is only on type of character in the string
// In : A string and the character to verify
// Out : 1 or 0 (1 = true, 0 = false).

int	is_ch(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != c)
			return (0);
	return (i);
}

// Fr :
// Desc : Fonctionne comme le echo de bash
// Entrée : Un tableau de chaines de caractères
// Sortie : 1 ou 0 (1 = pas d'erreur, 0 = erreur).
//
// En :
// Desc : Work like the bash's echo (we hope)
// In : A sting table
// Out : 1 or 0 (1 = no error, 0 = error).

void	ms_echo(char **table)
{
	int	i;

	i = -1;
	while (table[++i] != NULL && table[i][0] == '-'
		&& is_ch(&table[i][1], 'n'))
	{
		free(table[i]);
		table[i] = ft_strdup("-n");
	}
	while (table[i] != NULL)
	{
		write(1, table[i], ft_strlen(table[i]));
		if (table[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (table[0] == NULL || ft_strcmp(table[0], "-n") == 0)
		write(1, "\n", 1);
}
