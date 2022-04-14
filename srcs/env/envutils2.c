/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envutils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:09:22 by jforner           #+#    #+#             */
/*   Updated: 2022/03/31 17:44:27 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fr :
// Desc : Donne la variable d'environement qui a le même nom que "name",
//	si elle n'éxiste pas renvoie NULL.
// Entrée : Le pointeur de structure env, la liste de caractère a vérifier
// et la colonne à vérifier.
// Sortie : NULL ou la variable d'environement.
//
// En :
// Desc : Give the environment variable with the name "name"
// if it doesn't exist give NULL.
// In : The pointer of the structure env, the string to verify
// and the column to verify.
// Out : NULL ou the environment variable.

t_env	*envname(t_env **env, char *name, int column)
{
	t_env	*envtemp;

	envtemp = env[column];
	while (envtemp != NULL)
	{
		if (ft_strcmp(envtemp->name, name))
			break ;
		envtemp = envtemp->next;
	}
	if (envtemp == NULL)
		return (NULL);
	return (envtemp);
}

void	free_env(t_env *env)
{
	free(env->name);
	if (env->content != NULL)
		free(env->content);
	free(env);
}

void	free_export(t_env **env)
{
	while (env[1] != NULL)
	{
		free(env[1]->name);
		if (env[1]->content != NULL)
			free(env[1]->content);
		free(env[1]);
		env[1] = env[1]->next;
	}
	while (env[0] != NULL)
	{
		free(env[0]->content);
		free(env[0]->name);
		free(env[0]);
		env[0] = env[0]->next;
	}
	while (env[2] != NULL)
	{
		free(env[2]->content);
		free(env[2]->name);
		free(env[2]);
		env[2] = env[2]->next;
	}
}
