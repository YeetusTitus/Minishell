/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:40:40 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/25 16:27:32 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//permet d afficher le prompt et de garder l historique des commandes tapees
void	ft_loop(char **envp)
{
	t_lst	**s;
	t_env	*env[3];

	if (!*envp)
	{
		ft_putstr_fd("ca se fait pas de tester ca gros degueu\n", 2);
		exit(0);
	}
	create_env(env, envp);
	g_glob.retour = 0;
	while (1)
	{
		s = lexer(env);
		if (s)
			parsing(s, env);
	}
	system("leaks minishell");
}
//	free_env(*env);

t_lst	**lexer(t_env **env)
{
	t_lst	**s;
	char	*str;
	int		i;

	cwdisdel(env);
	str = readline("$> ");
	if (str == NULL)
		ms_exit(NULL);
	if (str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	if (ft_strlen(str) > 0)
		add_history(str);
	s = get_data_in_lst(str);
	i = get_qoute(s);
	if (i > 0)
	{
		free(str);
		free_lst(s);
		g_glob.retour = 258;
		return (NULL);
	}
	get_variable(s);
	get_variable_in_quote(s, env);
	translate_variable(s, env);
	free(str);
	return (s);
}

void	parsing(t_lst **s, t_env **env)
{
	t_redirection	r;

	r.s = s;
	r.red = NULL;
	r.simple_cmd = NULL;
	if (s == NULL)
		return ;
	r.i = check_pipe_place(s);
	if (r.i == 0)
		r = get_red(s, r);
	if (r.i == 0)
		execution(r.simple_cmd, env, r.red);
	if (r.i != 0)
	{

		free_red(r.red);
		r.simple_cmd = free_tab(r.simple_cmd);
		g_glob.retour = 258;
	}
	free_lst(s);
}

void	execution(char **s_cmd, t_env **env, t_red **red)
{
	int		save;
	int		pid;
	char	**envp;

	envp = get_env_array(env);
	if (s_cmd[0])
		ft_exec(red, s_cmd, envp, env);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			save = dup(1);
			dup_mannager_out(*red, 1, save, NULL);
			exit(0);
		}
		else
			wait(NULL);
	}
	envp = free_tab(envp);
	free_red(red);
//	s_cmd = free_tab(s_cmd);
}

t_redirection	get_red(t_lst **s, t_redirection r)
{
	r.i += get_redirection_with_file(s);
	if_only_red(s);
	r.red = get_red_array(s);
	r.simple_cmd = get_simple_cmd_array(s);
	return (r);
}