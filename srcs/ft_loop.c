#include "../include/minishell.h"

// la loop qui permet d afficher le prompt et de garder l historique des commandes tapees
void    ft_loop(char **envp)
{
	char    *str;
	t_lst   **s;
	t_env   *env[3]; // new version env a implemebter
	t_red   **red;
	char    **truc;
	int     save;
	int     i;
	int     pid;
	t_lst *lst;

	if (!*envp)
	{
		printf("ca se fait pas de tester ca gros degueu\n");
		exit(0);
	}
	create_env(env, envp);
	while (1)
	{
		truc = NULL;
		red = NULL;
		s = NULL;
		i = 0;
		str = readline("$> ");
		if (str == NULL)
			exit(0);
		if (ft_strlen(str) > 0)
			add_history(str);
		// lexer
		s = get_data_in_lst(str);
		get_qoute(s);
		////////////////////////////////       printf("quote ok\n");
		get_variable(s);
		get_variable_in_quote(s, env);
		translate_variable(s, env);
		//parsing
		i += check_pipe_place(s);
		if (i == 0)
		{
			i += get_redirection_with_file(s);
			if_only_red(s);
			red = get_red_array(s);
			truc = get_simple_cmd_array(s);
		}
		lst = *s;
		if (i == 0)
		{
			if (truc[0])
                ft_exec(red, truc, envp, env);
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
		}
		free(str);
		free_lst(s);
//		free_tab(truc);
		free_red(red);
	}
//	free_env(*env);
	system("leaks minishell");
}