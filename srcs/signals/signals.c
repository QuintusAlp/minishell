/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:56:01 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/03 16:31:31 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    void *signal(int sig, (*fct)(int))
    SIGINT = Ctrl-C
    SIGQUIT = Ctrl-\
*/

void    hangle_sigquit(int signal)
{
    (void)signal;
    rl_redisplay();
}

static void    handle_sigint(int signum)
{
    (void)signum;
    g_exitcode = 1;
    // printf("\n");
    // rl_replace_line("", 0);
    // rl_on_new_line();
    // rl_redisplay();
}

void    handle_signals(void)
{
    rl_catch_signals = 0;
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, hangle_sigquit);
}