/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:30:22 by jforner           #+#    #+#             */
/*   Updated: 2022/03/09 21:16:05 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_env	*env;
	t_env	*test;

	(void)(argc);
	(void)(argv);
	printf ("Yolo\n");
	create_env(&env, envp);
	i = -1;
	test = env;
	while (envp[++i] != NULL)
	{
		printf("%s=%s\n", test->name, test->content);
		free(test->name);
		free(test->content);
		test = test->next;
	}
	// system("leaks minishell");
	return (0);
}
