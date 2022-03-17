/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:48:46 by jforner           #+#    #+#             */
/*   Updated: 2022/03/17 15:11:50 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Fr :
// Desc : Si la variable éxiste l'enlève, sinon ne fait rien.
// Entrée : Le pointeur du pointeur des variables d'environements
// et le nom de la variable à supprimée.
// Sortie : 1 ou 0 (1 = pas d'erreur, 0 = erreur).
//
// En :
// Desc : If the variable existe supress it, else do nothing
// In : A pointer to a the pointert of the environments variables
// And the name of the variable to suppress.
// Out : 1 or 0 (1 = no error, 0 = error).

int	unset(t_env **env, char *name)
{
	unset_env(env, name);
	unset_export(env, name);
	if (!env_exist(env, name))
		return (1);
	return (1);
}

int	unset_export(t_env **env, char *name)
{
	t_env	*envtemp;

	if (env[1] == NULL)
		return (1);
	if (ft_strcmp(env[1]->name, name))
	{
		free(env[1]->name);
		free(env[1]);
		env[1] = env[1]->next;
		return (1);
	}
	envtemp = env[1];
	while (envtemp != NULL)
	{
		if (ft_strcmp(envtemp->next->name, name))
		{
			free(envtemp->next->name);
			free(envtemp->next);
			envtemp->next = envtemp->next->next;
			return (1);
		}
		envtemp = envtemp->next;
	}
	return (1);
}

int	unset_env(t_env **env, char *name)
{
	t_env	*envtemp;

	if (!env_exist(env, name))
		return (1);
	if (ft_strcmp((*env)->name, name))
	{
		free_env(*env);
		*env = (*env)->next;
		return (1);
	}
	envtemp = env[0];
	while (envtemp->next != NULL)
	{
		if (ft_strcmp(envtemp->next->name, name))
		{
			free_env(envtemp->next);
			envtemp->next = envtemp->next->next;
			return (1);
		}
		envtemp = envtemp->next;
	}
	return (1);
}

void	free_env(t_env *env)
{
	free(env->name);
	free(env->content);
	free(env);
}
