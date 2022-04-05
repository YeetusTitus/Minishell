/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:30:22 by jforner           #+#    #+#             */
/*   Updated: 2022/04/02 14:56:15 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strcpy(char *str)
{
	char	*cpy;
	int		i;

	cpy = (char *)malloc(ft_strlen(str) * sizeof(char) + 1);
	if (cpy == NULL)
		return (NULL);
	i = -1;
	while (++i < ft_strlen(str) + 1)
		cpy[i] = str[i];
	return (cpy);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env[3];
	char	**tabarg;
	char	**tabenv;
	char	*str;
	// char	*str2;
	int		i;

	(void)(argc);
	(void)(argv);
	tabarg = NULL;
	tabenv = NULL;
	int	j = -1;
	create_env(env, envp);
	while (++j < 20)
	{
		errno = 0;
		cwdisdel(env);
		i = -1;
		str = readline("minishell> ");
		tabarg = ft_split(str, ' ');
		if (!tablen(tabarg))
			export(env, NULL, NULL);
		else
		{
			if (ft_strcmp(tabarg[0], "unset"))
			{
				while (++i < tablen(tabarg))
					if (i > 0)
						unset(env, tabarg[i]);
			}
			else if (ft_strcmp(tabarg[0], "cd"))
			{
				if (tablen(tabarg) == 1)
					cd(env, NULL);
				else
					cd(env, ft_strdup(tabarg[1]));
			}
			else if (ft_strcmp(tabarg[0], "pwd"))
				pwd(env);
			else if(ft_strcmp(tabarg[0], "env"))
				print_env(*env);
			else if (ft_strcmp(tabarg[0], "echo"))
				ms_echo(&tabarg[1]);
			else
			{
				while (++i < tablen(tabarg))
				{
					if (!ft_strchr(tabarg[i], '='))
						export(env, ft_strcpy(tabarg[i]), NULL);
					else
					{
						if (tabenv != NULL)
							tabenv = ft_malloc_error(tabenv, tablen(tabenv));
						tabenv = ft_split(tabarg[i], '=');
						if (tablen(tabenv) > 1)
							export(env, ft_strcpy(tabenv[0]), ft_strcpy(tabenv[1]));
						else
							export(env, ft_strcpy(tabenv[0]), ft_strcpy("\0"));
					}
				}
			}
		}
		free (str);
		if (tabenv != NULL)
			tabenv = ft_malloc_error(tabenv, tablen(tabenv));
		if (tabarg != NULL)
			tabarg = ft_malloc_error(tabarg, tablen(tabarg));
	}
	free_export(env);
	// system("leaks minishell");
	return (0);
}
