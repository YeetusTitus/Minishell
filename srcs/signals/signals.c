/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jforner <jforner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:53:50 by jforner           #+#    #+#             */
/*   Updated: 2022/04/14 15:12:51 by jforner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handler_sig(int num)
{
	(void)(num);
	if (!g_sign && num == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_sign && num == 2)
		write(1, "\n", 1);
	if (g_sign && num == 3)
		write(1, "Quit: 3\n", 8);
}

void	sign_onoff(int toogle)
{
	struct termios	conf;

	tcgetattr(ttyslot(), &conf);
	if (toogle)
		conf.c_lflag |= ECHOCTL;
	else
		conf.c_lflag &= ~(ECHOCTL);
	tcsetattr(ttyslot(), 0, &conf);
	g_sign = toogle;
	if (toogle)
		signal(SIGQUIT, handler_sig);
	else
		signal(SIGQUIT, SIG_IGN);
}
