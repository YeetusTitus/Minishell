/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:30:22 by jforner           #+#    #+#             */
/*   Updated: 2022/03/10 14:42:40 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)(argc);
	(void)(argv);
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
