/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:35:53 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/12 16:57:49 by qalpesse         ###   ########.fr       */
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

static int    str_isdigit(char *str)
{
    int i;
    int result;

    i = 0;
    result = 1;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            result = 0;
        i++;
    }
    return (result);
}

void    exit_code(char *argv)
{
    int i;
    uint8_t nbr;

    i = 0;
    while (argv[i])
    {
        if (!(ft_isdigit(argv[i])) && !(argv[i] == '-' && i == 0))
        {
            ft_putstr_fd("bash: exit: ", 2);
            ft_putstr_fd(argv, 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            exit(g_exitcode);
        }
        i++;
    }
    nbr = ft_atoi(argv);
    exit (nbr);
}

void    ft_exit(char **argv, t_env **env)
{
    if ( argv[1] && argv[2] &&
            str_isdigit(argv[1]) && str_isdigit(argv[2]))
        {
            error("exit: too many arguments");
            g_exitcode = 1;
            return ;
        }
    if (*env)
        free_env(*env);
    ft_del_hdfiles();
    if (argv[1])
        exit_code(argv[1]);
    else 
        exit(0);
}