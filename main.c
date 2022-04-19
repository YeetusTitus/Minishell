/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:30:22 by jforner           #+#    #+#             */
/*   Updated: 2022/04/19 17:43:26 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_sign;

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
	static t_env	*env[3];
	char			**tabarg;
	char			**tabenv;
	char			*str;
	int				i;
	pid_t			pid;

	(void)(argc);
	(void)(argv);
	tabarg = NULL;
	tabenv = NULL;
	str = NULL;
	int	j = -1;
	char		**cato;

	cato = (char **)malloc(sizeof(char *) + 1);
	cato[0] = ft_strdup("/bin/cat");
	cato[1] = NULL;
	signal(SIGINT, handler_sig);
	sign_onoff(0);
	create_env(env, envp);
	while (++j < 5)
	{
		errno = 0;
		cwdisdel(env);
		i = -1;
		str = readline("minishell> ");
		if (!str)
			ms_exit(NULL, env);
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
				{
					char *dvd = ft_strdup(tabarg[1]);
					cd(env, dvd);
					free(dvd);
				}
			}
			else if (ft_strcmp(tabarg[0], "pwd"))
				pwd(env);
			else if(ft_strcmp(tabarg[0], "env"))
				print_env(*env);
			else if (ft_strcmp(tabarg[0], "echo"))
				ms_echo(&tabarg[1]);
			else if (ft_strcmp(tabarg[0], "cat"))
			{
				sign_onoff(1);
				pid = fork();
				if (pid == 0)
					execve(cato[0], cato, NULL);
				else
					wait(NULL);
				sign_onoff(0);
			}
			else if (ft_strcmp(tabarg[0], "exit"))
				ms_exit(&tabarg[1], env);
			else
			{
				while ((++i + 1) < tablen(tabarg))
				{
					if (!ft_strchr(tabarg[i], '='))
						export(env, ft_strdup(tabarg[i]), NULL);
					else
					{
						if (tabenv != NULL)
							tabenv = ft_malloc_error(tabenv, tablen(tabenv));
						tabenv = ft_split(tabarg[i], '=');
						if (tablen(tabenv) > 1)
							export(env, ft_strdup(tabenv[0]), ft_strdup(tabenv[1]));
						else
							export(env, ft_strdup(tabenv[0]), ft_strdup("\0"));
					}
				}
			}
		}
		free (str);
		str = NULL;
		if (tabenv != NULL)
			tabenv = ft_malloc_error(tabenv, tablen(tabenv));
		if (tabarg != NULL)
			tabarg = ft_malloc_error(tabarg, tablen(tabarg));
	}
	free(cato[0]);
	free(cato);
	free_export(env);
	system("leaks minishell");
	return (0);
}
