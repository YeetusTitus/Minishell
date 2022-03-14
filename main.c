/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:30:22 by jforner           #+#    #+#             */
/*   Updated: 2022/03/14 15:50:57 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_env	*env;
	char	*yo;
	char	*p;

	(void)(argc);
	(void)(argv);
	yo = ft_substr("o", 0, 1);
	p = ft_substr("Ok", 0, 2);
	create_env(&env, envp);
	i = -1;
	export(env, yo, p);
	print_env(env);
	printf("=================================\n");
	export(env, NULL, "OkIpullUp !");
	unset(&env, "o");
	print_env(env);
	// system("leaks minishell");
	return (0);
}
