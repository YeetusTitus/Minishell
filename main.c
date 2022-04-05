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
	int		i;
	t_env	*env;
	char	**tmp;
	char	*path;

	tmp = ft_split("ls -la", ' ');
	path = get_cmd(envp, tmp[0]);
	(void)(argc);
	(void)(argv);
	create_env(&env, envp);
	i = -1;
//	ft_loop(envp);
/*	export(env, "en Y", "Yolo");
	print_env(env);
	printf("=================================\n");
	export(env, "o", "Les Bois !");
	print_env(env);
*/	//system("leaks minishell");
system("leaks minishell");
execve(path, tmp, envp);
	return (0);
}
