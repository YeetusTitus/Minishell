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
	char	**truc;
	truc = malloc(sizeof(char *) * 2);
	truc[0] = ft_strdup("\0");
	truc[1] = NULL;
	(void)(argc);
	(void)(argv);
//	execve(NULL, truc, envp);
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
