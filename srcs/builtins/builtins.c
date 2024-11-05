/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:09:49 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/05 15:04:11 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// PQ ARGV[0] ET PAS JUSTE ARGV
// RETURNN ?

void builtins(t_cmd *cmd)
{
    if (ft_strncmp(cmd->argv[0], "echo", INT_MAX) == 0)
        return(echo(cmd->argv), exit(0));
    else if(ft_strncmp(cmd->argv[0], "env", INT_MAX) == 0)
        return(env(), exit(0)); // WHAT TO DO IF THERE ARE ARGS SINCE WE DONT NEED TO MANAGE THAT
    else if(ft_strncmp(cmd->argv[0], "export", INT_MAX) == 0)
        return(export(cmd->argv), exit(0));
    else if (ft_strncmp(cmd->argv[0], "pwd", INT_MAX) == 0)
        return(pwd(), exit(0));
    else if (ft_strncmp(cmd->argv[0], "unset", INT_MAX) == 0)
        return(unset((const char)cmd->argv), exit(0));
    else if (ft_strncmp(cmd->argv[0], "cd", INT_MAX) == 0)
        return(cd(cmd->argv[0]), exit(0));
    else if (ft_strncmp(cmd->argv[0], "exit", INT_MAX) == 0)
        return(ft_exit(cmd->argv), exit(0));
    else
        exit(1); // CORRECT ? 
}