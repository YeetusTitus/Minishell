/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envutils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:09:22 by jforner           #+#    #+#             */
/*   Updated: 2022/03/24 15:23:58 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Fr :
// Desc : Donne la variable d'environement qui a le même nom que "name",
//	si elle n'éxiste pas renvoie NULL.
// Entrée : Le pointeur de structure env et la liste de caractère a vérifier
// Sortie : NULL ou la variable d'environement.
//
// En :
// Desc : Give the environment variable with the name "name"
// if it doesn't exist give NULL.
// In : The pointer of the structure env and the string to verify.
// Out : NULL ou the environment variable.

t_env	*envname(t_env **env, char *name)
{
	t_env	*envtemp;

	envtemp = *env;
	while (envtemp != NULL)
	{
		if (ft_strcmp(envtemp->name, name))
			break ;
		envtemp = envtemp->next;
	}
	if (!ft_strcmp(envtemp->name, name))
		return (NULL);
	return (envtemp);
}
