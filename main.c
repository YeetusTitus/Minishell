/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:30:22 by jforner           #+#    #+#             */
/*   Updated: 2022/04/26 19:48:11 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_global	g_glob;

int	main(int argc, char **argv, char **envp)
{
	g_glob.retour = 0;
	(void)(argc);
	(void)(argv);
	signal(SIGINT, handler_sig);
	sign_onoff(0);
	ft_loop(envp);
	system("leaks minishell");
	return (0);
}
