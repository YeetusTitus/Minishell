/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:53:50 by jforner           #+#    #+#             */
/*   Updated: 2022/04/11 14:52:10 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handler_int(int num)
{
	(void)(num);
	write(1, "ligma\n", 6);
}

void	signals(void)
{
	struct sigaction	sig;

	sig.sa_flags = SA_RESTART;
	sig.__sigaction_u.__sa_handler = handler_int;
	sigaction(SIGINT, &sig, NULL);
	signal(SIGQUIT, SIG_IGN);
}
