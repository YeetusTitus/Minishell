/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:10:05 by jforner           #+#    #+#             */
/*   Updated: 2022/04/21 15:07:10 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fr :
// Desc : Vérifie si une variable d'environement avec comme nom "name" existe
// Entrée : Le pointeur de structure env et la liste de caractère a vérifier
// Sortie : 1 ou 0 (1 = éxiste, 0 = n'éxiste pas).
//
// En :
// Desc : Check if a environment variable with the name "name" exist
// In : The pointer of the structure env and the string to verify.
// Out : 1 or 0 (1 = exist, 0 = doesn't exist).

int	env_exist(t_env **env, char *name)
{
	t_env	*envtemp;

	envtemp = env[0];
	while (envtemp != NULL)
	{
		if (ft_strcmp(envtemp->name, name))
			return (1);
		envtemp = envtemp->next;
	}
	envtemp = env[1];
	while (envtemp != NULL)
	{
		if (ft_strcmp(envtemp->name, name))
			return (1);
		envtemp = envtemp->next;
	}
	envtemp = env[2];
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
// sinon rajoute une nouvelle variable d'environement ou une variable d'export
// si "content" est égal à NULL.
// et si la variable éxiste déjà change son contenu.
// Entrée : Le pointeur de structure env, le nom de la variable et son contenu
// Sortie : 1 ou 0 (1 = pas d'erreur, 0 = erreur).
// Note : N'envoyer que des chaînes de caractères allouer.
//
// En :
// Desc : if "name" est NULL display the environments variables
// else add a new environment variable or an export variable if content is NULL
// and if the variable already exist change it's content.
// In : The pointer of the stockage variable,
// the name of the variable and it content.
// Out : 1 or 0 (1 = no error, 0 = error).
// Note : Only add allocated strings.

int	export(t_env **env, char *name, char *content)
{
	if (name == NULL)
		return (print_export(env));
	g_glob.retour = env_error(name, content, 'e');
	if (g_glob.retour)
		return (g_glob.retour);
	if (content == NULL)
	{
		if (!env_exist(env, name))
		{
			if (env[1] == NULL)
				env[1] = envnew(name, NULL);
			else
				envadd_back(&env[1], envnew(name, NULL));
		}
		else if (envname(env, name, 2) != NULL)
			export(env, name, ft_strdup(envname(env, name, 2)->content));
		else
			free(name);
	}
	else
		if (!export_env(env, name, content))
			return (1);
	return (0);
}

// Fr :
// Desc : Continuité de export().
// Note : Supprime la variable d'export si il y a un doublon dans env.
//
// En :
// Desc : Continuity of export().
// Note : Suppress the export variable if ditto in env.

int	export_env(t_env **env, char *name, char *content)
{
	t_env	*envtemp;

	envtemp = *env;
	unset_export(env, name);
	if (!envname(env, name, 0))
		envadd_back(env, envnew(name, content));
	else if (envname(env, name, 0) != NULL || envname(env, name, 1) != NULL)
	{
		while (envtemp != NULL)
		{
			if (ft_strcmp(envtemp->name, name))
			{
				free(envtemp->name);
				free(envtemp->content);
				envtemp->content = content;
				envtemp->name = name;
				return (1);
			}
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

int	print_export(t_env **env)
{
	t_env	*envtemp;

	envtemp = env[0];
	while (envtemp != NULL)
	{
		printf("declare -x %s=\"%s\"\n", envtemp->name, envtemp->content);
		envtemp = envtemp->next;
	}
	envtemp = env[1];
	while (envtemp != NULL)
	{
		if (envtemp->content == NULL)
			printf("declare -x %s\n", envtemp->name);
		else
			printf("declare -x %s=\"%s\"\n", envtemp->name, envtemp->content);
		envtemp = envtemp->next;
	}
	return (0);
}
