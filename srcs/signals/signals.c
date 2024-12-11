/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:56:01 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/11 12:23:07 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    void *signal(int sig, (*fct)(int))
    SIGINT = Ctrl-C
    SIGQUIT = Ctrl-\
*/

static void set_ctrl_d(int mode)
{
    struct termios term;
    tcgetattr(0, &term);
    if (mode == 1)
    {
        term.c_cc[VEOF] = 4;
        term.c_lflag &= ~(ECHOCTL);
    }
    else if(mode == 2)
    {
       term.c_cc[VEOF] = _POSIX_VDISABLE;
        term.c_lflag &= ~(ECHOCTL);
    }
    else if(mode == 3)
    {
        term.c_cc[VEOF] = 4;
        term.c_lflag &= ~(ECHOCTL);
    }
    tcsetattr(0, TCSANOW, &term);
}
void default_sigint(int sig)
{
	(void)sig;
	//g_signal = SIGINT;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_display();
}
void sigint_block(int sig)
{
	(void)sig;
	// g_signal = sig;
	if (sig == SIGQUIT)
		write(1, "QUIT:3", 7);
	write(1, "\n", 1);
}
void sigint_process(int sig)
{
	(void)sig;
	// g_signal = SIGINT;
	write(1, "\n", 1);
}
void ft_set_sig(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, default_sigint);
		signal(SIGQUIT, SIG_IGN);
		set_ctrl_d(1);
	}
	if (mode  == 2)
	{
		signal(SIGINT, sigint_process);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == 3)
	{
		signal(SIGINT, sigint_block);
		signal(SIGQUIT, sigint_block);
		set_ctrl_d(2);
	}
	if (mode == 4)
	{
		signal(SIGINT, sigint_process);
		signal(SIGQUIT, exit);
		set_ctrl_d(3);
	}
}




