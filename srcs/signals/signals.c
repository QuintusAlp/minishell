/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:56:01 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/24 09:55:07 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_set_term(int mode)
{
	struct termios	term;

	tcgetattr(0, &term);
	if (mode == 1)
	{
		term.c_lflag &= ~(ECHOCTL);
	}
	if (mode == 2)
	{
		term.c_lflag |= (ECHOCTL);
	}
	tcsetattr(0, TCSANOW, &term);
}

void	ft_default_sig(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_no_actions(int sig)
{
	(void)sig;
}

void	ft_block(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("Quit: 3\n");
		g_exitcode = 131;
	}
	else if (sig == SIGINT)
	{
		printf("\n");
		g_exitcode = 130;
	}
}

void	ft_set_sig(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, ft_default_sig);
		signal(SIGQUIT, SIG_IGN);
		ft_set_term(1);
	}
	if (mode == 2)
	{
		signal(SIGINT, ft_no_actions);
		signal(SIGQUIT, SIG_IGN);
		ft_set_term(2);
	}
	if (mode == 3)
	{
		signal(SIGINT, ft_block);
		signal(SIGQUIT, ft_block);
		ft_set_term(2);
	}
	else
		return ;
}
