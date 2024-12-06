/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:56:01 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/06 16:25:37 by qalpesse         ###   ########.fr       */
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

static void    handle_sigint(int signum, siginfo_t *info, void *other)
{
    (void)signum;
    (void)info;
    (void)other;
    // printf("pid: %d", info->si_pid);
    g_exitcode = 1;
    printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}
static void    handle_sigint_hd(int signum, siginfo_t *info, void *other)
{
    (void)signum;
    (void)info;
    (void)other;
    
    // printf("\n");
    // // printf("pid: %d", info->si_pid);
    // rl_replace_line("", 0);
    // rl_on_new_line();
    // rl_redisplay();
    exit(1);
}

void    handle_signals(void)
{
    struct sigaction sa;
    sa.sa_handler = NULL;
    sa.sa_sigaction = handle_sigint;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    rl_catch_signals = 0;
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, hangle_sigquit);
}

void handle_child_signals(void)
{
     struct sigaction sa;
    sa.sa_handler = NULL;
    sa.sa_sigaction = handle_sigint_hd;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    rl_catch_signals = 0;
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, hangle_sigquit);
    
}

void ignore_sigint(void)
{
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    
}


