/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:40:40 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/22 16:21:10 by jforner          ###   ########.fr       */
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
		printf("ca se fait pas de tester ca gros degueu\n");
		exit(0);
	}
	create_env(env, envp);
	g_retour = 0;
	while (1)
	{
		s = lexer(env);
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

	str = readline("$> ");
	if (str == NULL)
		ms_exit(NULL);
	if (ft_strlen(str) > 0)
		add_history(str);
	s = get_data_in_lst(str);
	i = get_qoute(s);
	if (i > 0)
	{
		free(str);
		free_lst(s);
		g_retour = 258;
		return (NULL);
	}
	get_variable(s);
	get_variable_in_quote(s, env);
	translate_variable(s, env);
	free(str);
	t_lst *lst = *s;
	while (lst)
	{
		printf("type == %d - data == %s\n", lst->type, lst->data);
		lst = lst->next;
	}
	return (s);
}

void	parsing(t_lst **s, t_env **env)
{
	int		i;
	t_red	**red;
	char	**simple_cmd;

	if (s == NULL)
		return ;
	i = check_pipe_place(s);
	if (i == 0)
	{
		i += get_redirection_with_file(s);
		if_only_red(s);
		red = get_red_array(s);
		simple_cmd = get_simple_cmd_array(s);
	}
	if (i == 0)
		execution(simple_cmd, env, red);
	if (i != 0)
		g_retour = 258;
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
		wait(NULL);
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
	free_tab(envp);
	free_red(red);
//	free_tab(s_cmd);
}
