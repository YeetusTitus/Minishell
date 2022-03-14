/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:10:05 by jforner           #+#    #+#             */
/*   Updated: 2022/03/14 16:02:18 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Fr :
// Desc : Vérifie si une variable d'environement avec comme nom "name" existe
// Entrée : Le pointeur de structure env et la liste de caractère a vérifier
// Sortie : 1 ou 0 (1 = éxiste, 0 = n'éxiste pas).
//
// En :
// Desc : Check if a environment variable withe the name "name" exist
// In : The pointer of the structure env and the string to verify.
// Out : 1 or 0 (1 = exist, 0 = doesn't exist).

int	env_exist(t_env *env, char *name)
{
	t_env	*envtemp;

	envtemp = env;
	while (envtemp != NULL)
	{
		if (ft_strcmp(envtemp->name, name))
			return (1);
		envtemp = envtemp->next;
	}
	return (0);
}

// Fr :
// Desc : Si "name" est NULL affiche les variables d'environements
// sinon rajoute une nouvelle variable d'environement
// et si la variable éxiste déjà change son contenu.
// Entrée : Le pointeur de structure env, le nom de la variable et son contenu
// Sortie : 1 ou 0 (1 = pas d'erreur, 0 = erreur).
// Note : N'envoyer que des chaînes de caractères allouer.
//
// En :
// Desc : if "name" est NULL display the environments variables
// else add a new environment variable
// and if the variable already exist change it's content.
// In : The pointer of the stockage variable,
// the name of the variable and it content.
// Out : 1 or 0 (1 = no error, 0 = error).
// Note : Only add allocated strings.

int	export(t_env *env, char *name, char *content)
{
	t_env	*envtemp;

	envtemp = env;
	if (name == NULL)
	{
		print_export(env);
		return (1);
	}
	if (!env_exist(env, name))
		envadd_back(&env, envnew(name, content));
	else
	{
		while (envtemp != NULL)
		{
			if (envtemp->name == name)
				envtemp->content = content;
			envtemp = envtemp->next;
		}
	}
	return (1);
}

// Fr :
// Desc : Affiche les variables d'environements.
//
// En :
// Desc : Display the environments variables.

void	print_env(t_env *env)
{
	t_env	*envtemp;

	envtemp = env;
	while (envtemp != NULL)
	{
		printf("%s=%s\n", envtemp->name, envtemp->content);
		envtemp = envtemp->next;
	}
}

// Fr :
// Desc : Affiche les variables d'environements de la manière d'export
//
// En :
// Desc : Display the environments variables like export does.

void	print_export(t_env *env)
{
	t_env	*envtemp;

	envtemp = env;
	while (envtemp != NULL)
	{
		printf("declare -x %s=\"%s\"\n", envtemp->name, envtemp->content);
		envtemp = envtemp->next;
	}
}
