/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:35:53 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/02 16:41:57 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    --> without arg: exit
        terminates the current shell/script
    --> with one SINGLE numeric arg: exit 42
        exits with code 42
        the value muste be [0 ; 255], 
            if nbr > 255 -> changed to % 256 to be in the range
            if nbr < 0 --> changed to 256 - nbr
    --> MULTIPLE ARGS / NON-NUMERIC : error
*/

void    exit_code(char *argv)
{
    int i;
    int nbr;
    
    i = 0;
    while (argv[i])
    {
        if (!(ft_isdigit(argv[i])))
        {
                g_exitcode = 1;
               error("error: exit --> non-numeric character in the argument"); // moddifier le erreur message
               return ;
        }
        i++;
    }
    nbr = ft_atoi(argv);
    if (nbr >= 0 && nbr <= 255)
        g_exitcode = nbr;
    else if (nbr >= -255 && nbr < 0)
        g_exitcode = 256 + nbr;
    else if (nbr < -255)
        g_exitcode = -nbr % 256;
    else if (nbr > 255)
        g_exitcode = nbr % 256;
    exit(g_exitcode);
}

void    ft_exit(char **argv, t_env **env)
{
    (void)env;
    if (argv[1] && argv[2])
        error("exit: too many arguments");
    if (*env)
        free_env(*env);
    ft_del_hdfiles();
    if (argv[1])
        exit_code(argv[1]);
    else 
        exit(0);
}