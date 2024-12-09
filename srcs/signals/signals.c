/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:56:01 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/09 17:02:22 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    void *signal(int sig, (*fct)(int))
    SIGINT = Ctrl-C
    SIGQUIT = Ctrl-\
*/

static void    handle_sigint(int signum)
{
    (void)signum;
    g_exitcode = 1;
    write(1, "\n", 1);
//     rl_replace_line("", 0);
//     rl_on_new_line();
//     rl_redisplay();
}

static void    handle_sigint_bis(int signum)
{
    (void)signum;
    g_exitcode = 0;
    printf("coucou \n");
    exit(1);
//     rl_replace_line("", 0);
//     rl_on_new_line();
//     rl_redisplay();
	// rl_done = 1; 
}

// SI DANS UN CHILD RL_CATCH_SIGNALS = 1
void    handle_signals(void)
{
    rl_catch_signals = 0;
    //-- ctr + c--
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    //-- ctrl + d --
    signal(SIGQUIT, SIG_IGN);
}

void    handle_signals_bis(void)
{
    rl_catch_signals = 0;
    signal(SIGINT, handle_sigint_bis);
    signal(SIGQUIT, SIG_IGN);
}


