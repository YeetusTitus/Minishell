/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:07:27 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/26 14:25:37 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// concatener les $ avec le texte qui le suit
void	get_variable(t_lst **s)
{
	t_lst	*lst;

	lst = *s;
	while (lst)
	{
		if (lst->type == '$')
		{
			if (lst->next->type == -1)
			{
				lst->data = ft_strjoin_v2(lst->data, lst->next->data);
				lst_del(s, lst->pos + 1);
				lst->type = '$';
			}
			else
			{
				lst->type = -1;
			}
		}
		lst = lst->next;
	}
}

//pour les variables entre double quote (avec et sans texte avant le $variable)
void	translate_variable(t_lst **s, t_env **env)
{
	t_lst	*lst;
	t_env	**tmp;
	char	*tmp2;
	int		i;

	i = 0;
	lst = *s;
	tmp2 = NULL;
	tmp = env;
	while (lst)
	{
		if (lst->type == '$')
			get_variable_case_1(lst, tmp, s);
		else if (lst->type == -2)
			get_variable_case_2(lst, tmp, tmp2, i);
		i = 0;
		tmp = env;
		if (lst)
			lst = lst->next;
	}
}

// loop de la fonction du dessus pour la norme
void	get_variable_case_1(t_lst *lst, t_env **tmp, t_lst **s)
{
	int	i;

	i = 0;
	if (ft_strcmp(lst->data, "$?") == 1)
	{
		free(lst->data);
		lst->data = ft_itoa(g_glob.retour);
		lst->type = -1;
		return ;
	}
	while (i < 3)
	{
		if (envname(tmp, lst->data + 1, i) != NULL
			&& !ft_strcmp(lst->data + 1, "."))
		{
			if (envname(tmp, lst->data + 1, i)->content[0] == '\0')
				lst_del(s, lst->pos);
			else
				free_lst_data(lst, envname(tmp, lst->data + 1, i));
			return ;
		}
		i += 2;
	}
	lst_del(s, lst->pos);
}

// idem que case 1
void	get_variable_case_2(t_lst *lst, t_env **env, char *tmp2, int i)
{
	int		j;

	j = 0;
	while (lst->data[i] != '$' && lst->data[i])
		i++;
	if (i < ft_strlen_v2(lst->data))
	{
		while (j < 3)
		{
			if (envname(env, lst->data + i + 1, j) != NULL
				&& !ft_strcmp(lst->data + 1, "."))
			{
				tmp2 = ft_strndup(lst->data, i);
				free(lst->data);
				lst->data = ft_strjoin_v2(tmp2, envname(env, tmp2, j)->content);
				return ;
			}
			j += 2;
		}
		get_v_case_2_loop(lst, i, tmp2);
	}
	lst->type = -1;
}

void	get_v_case_2_loop(t_lst *lst, int i, char *tmp2)
{
	char	*tmp;

	tmp = ft_strndup(lst->data, i);
	while (lst->data[++i])
	{
		if (lst->data[i] == ' ' || lst->data[i] == '$')
			break ;
	}
	tmp2 = ft_strdup(lst->data + i);
	free(lst->data);
	lst->data = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
}
