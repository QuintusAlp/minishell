/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:09:49 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/05 14:43:50 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// EXIT PARTT
void builtins(t_cmd *cmd)
{
    if (ft_strncmp(cmd->argv[0], "echo", INT_MAX) == 0)
        return(echo(cmd->argv), exit(0));
    else if(ft_strncmp(cmd->argv[0], "env", INT_MAX) == 0)
        env(); // WHAT TO DO IF THERE ARE ARGS SINCE WE DONT NEED TO MANAGE THAT
    else if(ft_strncmp(cmd->argv[0], "export", INT_MAX) == 0)
        export(cmd->argv);
    else if (ft_strncmp(cmd->argv[0], "pwd", INT_MAX) == 0)
        pwd();
    else if (ft_strncmp(cmd->argv[0], "unset", INT_MAX) == 0)
        unset((const char)cmd->argv);
    else if (ft_strncmp(cmd->argv[0], "cd", INT_MAX) == 0)
        cd(); //COMPLETE
    else if (ft_strncmp(cmd->argv[0], "exit", INT_MAX) == 0)
        ft_exit(cmd->argv);
    else 
}