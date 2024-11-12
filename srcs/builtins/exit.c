/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:35:53 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/12 15:24:22 by qalpesse         ###   ########.fr       */
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
    int exit_code;
    
    i = 0;
    exit_code = 0;
    while (argv[i])
    {
        if (!(ft_isdigit(argv[i])))
            error("error: exit --> non-numeric character in the argument");
        i++;
    }
    nbr = ft_atoi(argv);
    if (nbr >= 0 && nbr <= 255)
        exit_code = nbr;
    else if (nbr >= -255 && nbr < 0)
        exit_code = 256 + nbr;
    else if (nbr < -255)
        exit_code = -nbr % 256;
    else if (nbr > 255)
        exit_code = nbr % 256;
    exit(exit_code);
}

void    ft_exit(char **argv, t_env **env)
{
    printf("exiiit\n");
    if (argv[1] && argv[2])
        error("exit: too many arguments");
    free_env(*env);
    if (argv[1])
        exit_code(argv[1]);
    else 
        exit(0);
}