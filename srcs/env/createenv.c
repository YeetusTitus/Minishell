/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:49:36 by jforner           #+#    #+#             */
/*   Updated: 2022/04/22 15:22:22 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fr : 
// Desc : Similaire à strlen,
// mais commence de compter après le prochain charactère égal à chr.
// 
// En :
// Desc : Similar to strlen,
// but begin to count after the next character egal to chr.

int	lenachr(char *str, char chr)
{
	int	count;
	int	test;

	test = 0;
	count = 0;
	while (*str)
	{
		if (test)
			count++;
		else if (*str == chr)
			test++;
		str++;
	}
	return (count);
}

// Fr : 
// Desc : Similaire à strlen,
// mais s'arrête quand le caractère actuel est égal à chr.
// 
// En :
// Desc : Similar to strlen, but stop when the actual character is egal to chr.

int	lenbchr(char *str, char chr)
{
	int	count;

	count = 0;
	while (*str && *str != chr)
	{
		count++;
		str++;
	}
	return (count);
}

// Fr :
// Desc : Intègre les informations de la ligne actuelle d'Envp dans
// la variable de stockage des information pour la variable d'environnement.
// Entrée : Le pointeur de la variable de stockage des information
//	et la ligne actuel de Envp.*
// Sortie : 1 ou 0 (1 = pas d'erreur, 0 = erreur).
//
// En :
// Desc : Dump the information on the actual line of Envp in the
// stockage variable of information for the environment variable.
// In : The pointer of the stockage variable and the actual line of Envp.*
// Out : 1 or 0 (1 = no error, 0 = errorr).

char	**content_env(char **cont, char *line)
{
	cont[0] = ft_substr(line, 0, lenbchr(line, '='));
	cont[1] = ft_substr(line, lenbchr(line, '=') + 1, ft_strlen(line));
	if (cont[0] == NULL || cont[1] == NULL)
	{
		if (cont[0] != NULL)
			free(cont[0]);
		if (cont[1] != NULL)
			free(cont[1]);
		free(cont);
		return (NULL);
	}
	return (cont);
}

// Fr :
// Desc : créer la structure de la variable d'environement
// Entrée : Un pointeur sur le table d'environements et le variable Envp.*
// Sortie : 1 ou 0 (1 = pas d'erreur, 0 = erreur).
//
// En :
// Desc : create the structure of the environment variable.
// In : A pointer on the  structure of
// the environment variable and the Envp variable .*
// Out : 1 or 0 (1 = no error, 0 = error).

int	create_env(t_env **env, char **envp)
{
	int		i;
	char	**cont;

	env[1] = NULL;
	env[2] = NULL;
	cont = (char **)malloc(3 * sizeof(char *));
	cont[2] = NULL;
	i = 0;
	cont = content_env(cont, envp[i]);
	if (cont == NULL)
		return (0);
	*env = envnew(cont[0], cont[1]);
	while (envp[++i] != NULL)
	{
		cont = content_env(cont, envp[i]);
		if (cont == NULL)
			return (0);
		envadd_back(env, envnew(cont[0], cont[1]));
	}
	unset(env, "OLDPWD");
	env[1] = envnew(ft_strdup("OLDPWD"), NULL);
	env[2] = envnew(ft_strdup("."), getcwd(NULL, 0));
	free(cont);
	return (1);
}
