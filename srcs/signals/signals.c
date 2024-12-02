/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:56:01 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/01 21:16:27 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    void *signal(int sig, (*fct)(int))
    SIGINT = Ctrl-C
    SIGQUIT = Ctrl-\
*/

// static void    handle_sigint(int signum)
// {
//     (void)signum;
//     if (signum == SIGINT)
//     {
//         write(1, "\n", 1);
//         rl_replace_line("", 0);
//         rl_on_new_line();
//         rl_redisplay();
//     }
// }

// void    handle_signals()
// {
//     (void)handle_sigint(SIGINT);
//     signal(SIGINT, handle_sigint);
//     signal(SIGQUIT, SIG_IGN);
// }