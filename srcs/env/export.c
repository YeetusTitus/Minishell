/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:10:05 by jforner           #+#    #+#             */
/*   Updated: 2022/03/10 15:36:32 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_exist(t_env *env, char *name)
{
	t_env	*envtemp;

	envtemp = env;
	while (envtemp != NULL)
	{
		if (envtemp->name == name)
			return (1);
		envtemp = envtemp->next;
	}
	return (0);
}

void	export(t_env *env, char *name, char *content)
{
	t_env	*envtemp;

	envtemp = env;
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
}

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
