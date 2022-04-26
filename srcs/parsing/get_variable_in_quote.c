/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable_in_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:07:31 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/26 15:11:50 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	get_variable_in_quote(t_lst **s, t_env **envp)
{
	t_lst	*lst;

	lst = *s;
	while (lst)
	{
		if (lst->type == -2)
			get_variable_in_quote_loop(lst, envp);
		lst = lst->next;
	}
}

void	get_variable_in_quote_loop(t_lst *lst, t_env **envp)
{
	int		i;
	char	*variable;
	char	*data;
	char	*end;

	i = 0;
	while (lst->data[i] != '$' && lst->data[i])
		i++;
	if (ft_strlen_v2(lst->data) == i)
	{
		lst->type = -1;
		return ;
	}
	data = ft_strndup(lst->data, i);
	variable = get_variable_name(envp, i + 1, lst);
	end = get_end_variable(lst);
	free(lst->data);
	lst->data = ft_strdup(data);
	lst->data = ft_strjoin_v2(lst->data, variable);
	lst->data = ft_strjoin_v2(lst->data, end);
	free(data);
	free(variable);
	free(end);
}

char	*get_variable_name(t_env **envp, int i, t_lst *lst)
{
	char	*variable;
	int		j;

	j = i;
	while (lst->data[j])
	{
		if (lst->data[j] == ' ' || lst->data[j] == '\'' || lst->data[j] == '"'
			|| lst->data[j] == ';' || lst->data[j] == '.' || lst->data[j] == ','
			|| lst->data[j] == '\\' || lst->data[j] == '>'
			|| lst->data[j] == '<')
			break ;
		j++;
	}
	variable = ft_strndup(lst->data + i, j - i);
	variable = env_name_loop(envp, variable);
	return (variable);
}

char	*env_name_loop(t_env **env, char *variable)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!env[i] || !env[i]->content)
			i++;
		if (ft_strcmp(variable, env[i]->name) == 1)
		{
			free(variable);
			variable = ft_strdup(env[i]->content);
			return (variable);
		}
		env[i] = env[i]->next;
		if (env[i]->next == NULL)
			i++;
	}
	variable = ft_strdup("\0");
	return (variable);
}

char	*get_end_variable(t_lst *lst)
{
	int		j;
	char	*end;

	j = 0;
	while (lst->data[j] != '$' && lst->data[j])
		j++;
	while (lst->data[j] != ' ' && lst->data[j] != '\'' && lst->data[j] != '"'
		&& lst->data[j] != ';' && lst->data[j] != '.'
		&& lst->data[j] != ',' && lst->data[j] != '\\' && lst->data[j] != '>'
		&& lst->data[j] != '<' && lst->data[j])
		j++;
	end = ft_strdup(lst->data + j);
	return (end);
}
