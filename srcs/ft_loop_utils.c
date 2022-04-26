/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktroude <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:46:59 by ktroude           #+#    #+#             */
/*   Updated: 2022/04/26 19:47:01 by ktroude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lst	**return_lst(t_lst **s, char *str)
{
	free(str);
	free_lst(s);
	g_glob.retour = 258;
	return (NULL);
}

t_redirection	get_red(t_lst **s, t_redirection r)
{
	r.i += get_redirection_with_file(s);
	if_only_red(s);
	r.red = get_red_array(s);
	r.simple_cmd = get_simple_cmd_array(s);
	return (r);
}
