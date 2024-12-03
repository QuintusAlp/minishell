/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:56:01 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/03 14:33:21 by marlonco         ###   ########.fr       */
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
    g_exitcode = 0;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

// SI DANS UN CHILD RL_CATCH_SIGNALS = 1
void    handle_signals(void)
{
    rl_catch_signals = 0;
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}