/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:33:05 by jforner           #+#    #+#             */
/*   Updated: 2022/03/14 14:32:15 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fr :
// Toutes les fonctions pour les listes chaînées pour la structure env
// En :
// All the functions for the linked lists for env structure

t_env	*envnew(char *name, char *content)
{
	t_env	*liste;

	liste = malloc(sizeof(t_env));
	liste->content = content;
	liste->name = name;
	liste->next = NULL;
	return (liste);
}

int	envsize(t_env *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_env	*envlast(t_env *lst)
{
	t_env	*liste;

	liste = lst;
	while (liste->next != NULL)
		liste = liste->next;
	return (liste);
}

void	envadd_back(t_env **alst, t_env *new)
{
	envlast(*alst)->next = new;
}

void	envadd_front(t_env **alst, t_env *new)
{
	new->next = alst[0];
	alst[0] = new;
}
