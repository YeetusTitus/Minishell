/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envutils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:09:22 by jforner           #+#    #+#             */
/*   Updated: 2022/04/27 11:40:56 by jforner          ###   ########.fr       */
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

int	env_error_chr(char *name)
{
	int	i;

	i = -1;
	if (name[0] == '-')
		return (2);
	while (name[++i])
	{
		if ((name[0] >= '0' && name[0] <= '9'))
			return (1);
		if (name[i] < 'A' || name[i] > 'Z')
			if (name[i] < 'a' || name[i] > 'z')
				if (name[i] != '_')
					if (name[i] < '0' || name[i] > '9')
						return (1);
	}
	return (0);
}

int	env_error(char *name, char *content, char c)
{
	g_glob.ret = env_error_chr(name);
	if (g_glob.ret)
	{
		write(2, "minishell: ", 11);
		if (c == 'e')
			write(2, "export: ", 8);
		else if (c == 'u')
			write(2, "unset: ", 7);
		write(2, name, ft_strlen(name));
		if (c == 'e' && content != NULL)
		{
			write(2, "=", 1);
			write(2, content, ft_strlen(content));
		}
		if (g_glob.ret == 2)
			ft_putstr_fd(" : invalid option\n", 2);
		else
			write(2, ": not a valid identifier\n", 25);
		if (c == 'e')
			free(name);
		if (content)
			free(content);
		return (g_glob.ret);
	}
	return (0);
}
