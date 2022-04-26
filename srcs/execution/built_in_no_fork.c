/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_no_fork.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:55:14 by jforner           #+#    #+#             */
/*   Updated: 2022/04/25 18:55:16 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset_no(t_built b, t_env **env)
{
	b.ret = unset_no_fork(b, env);
	return (0);
}

int	export_no(t_built b, t_env **env)
{
	b.ret = export_no_fork(b, env);
	return (b.ret);
}

int	cd_no(t_built b, char *simple_cmd, t_env **env)
{
	b.ret = cd_no_fork(b, env, simple_cmd);
	return (b.ret);
}

int	exit_no(t_built b)
{
	ms_exit(b.table + 1);
	free_tab(b.table);
	return (0);
}
