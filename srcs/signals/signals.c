/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:56:01 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/11 14:49:54 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    void *signal(int sig, (*fct)(int))
    SIGINT = Ctrl-C
    SIGQUIT = Ctrl-\
*/

void ft_default_sig(int sig)
{
    (void)sig;
    printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}
void ft_no_actions(int sig)
{
    (void)sig;
}
void ft_block(int sig)
{
    if(sig == SIGQUIT)
    {
        printf("^\\Quit: 3\n");
        g_exitcode = 131;
    }
    else if (sig == SIGINT)
    {
        printf("^C\n");
        g_exitcode = 131;
    }
}
void ft_set_sig(int mode)
{
    if(mode == 1)
    {
        signal(SIGINT, ft_default_sig);
        signal(SIGQUIT, SIG_IGN);
    }
    if (mode == 2)
    {
        signal(SIGINT, ft_no_actions);
        signal(SIGQUIT, SIG_IGN);
    }
    if(mode == 3)
    {
        signal(SIGINT, ft_block);
        signal(SIGQUIT, ft_block);
    }
    else
        return ;
}




