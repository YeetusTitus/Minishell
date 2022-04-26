/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:33:45 by jforner           #+#    #+#             */
/*   Updated: 2022/04/22 15:05:06 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fr :
// Desc : Vérifie si il n'y a pas d'erreur pour exit
// Entrée : Un tableau de chaines de caractères
// Sortie : -1, -2 ou [0-255] (-1(255) et -2 = erreur, [0-255] = numérot d'exit)
// Erreur : -1 = n'est pas un argument valide (execute exit ensuite)
// -2 = a plusieur arguments (n'execute pas exit)
//
// En :
// Desc : Display "exit" and check if ther is no error in for exit
// In : A string table
// Out : -1, -2 ou [0-255] (-1(255) and -2 = error, [0-255] = exit number)
// Error : -1 = not a valide argumments (execute exit afterward)
// -2 = multiple argumments (don't execute exit)

int	exit_error(char **table)
{
	if (!verif_isdigit(*table) || !verif_maxlong(*table))
	{
		write(2, "minishell: exit: ", 17);
		write(2, *table, ft_strlen(*table));
		write(2, ": numeric argument required\n", 28);
		return (255);
	}
	if (tablen(table) > 1)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (-1);
	}
	return (ms_atouc(*table));
}

// Fr :
// Desc : Affiche "exit\n" et termine le programme si il n'y a pas d'erreur
// Entrée : Un tableau de chaines de caractères et env
//
// En :
// Desc : Display "exit" and terminate the program if there is no error
// In : A string table and env

void	ms_exit(char **table)
{
	int	status;

	printf("exit\n");
	if (table == NULL || !tablen(table))
		exit(g_glob.retour);
	status = exit_error(table);
	if (status >= 0)
	{
		g_glob.retour = status;
		exit(status);
	}
	else
		g_glob.retour = 1;
}
