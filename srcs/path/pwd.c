/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:28:42 by jforner           #+#    #+#             */
/*   Updated: 2022/04/22 16:13:23 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd_special(t_env **env, char **path)
{
	if (*path == NULL || (int)*path[0] == 0)
	{
		if (envname(env, "HOME", 0) == NULL)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (0);
		}
		*path = ft_strdup(envname(env, "HOME", 0)->content);
		return (1);
	}
	return (2);
}

int	pwd(t_env **env)
{
	printf("%s\n", (envname(env, ".", 2))->content);
	return (1);
}
