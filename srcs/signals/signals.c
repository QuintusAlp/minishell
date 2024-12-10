/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:56:01 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/10 16:45:54 by qalpesse         ###   ########.fr       */
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




