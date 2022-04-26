/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:30:22 by jforner           #+#    #+#             */
/*   Updated: 2022/04/21 11:34:03 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"


t_global g_glob;

int	main(int argc, char **argv, char **envp)
{
	g_glob.retour = 0;
	(void)(argc);
	(void)(argv);
	signal(SIGINT, handler_sig);
	sign_onoff(0);
	ft_loop(envp);
/*	export(env, "en Y", "Yolo");
	print_env(env);
	printf("=================================\n");
	export(env, "o", "Les Bois !");
	print_env(env);
*/	//system("leaks minishell");
system("leaks minishell");
	return (0);
}
