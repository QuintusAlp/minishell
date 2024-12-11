/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:09:49 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/11 14:53:53 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtins(t_cmd *cmd)
{
	if (ft_strncmp(cmd->argv[0], "echo", INT_MAX) == 0)
		return (echo(cmd->argv), exit(0));
	else if (ft_strncmp(cmd->argv[0], "env", INT_MAX) == 0)
		return (env(cmd->g_env), exit(0));
	else if (ft_strncmp(cmd->argv[0], "export", INT_MAX) == 0)
		return (export(cmd->argv, cmd->g_env), exit(0));
	else if (ft_strncmp(cmd->argv[0], "pwd", INT_MAX) == 0)
		return (pwd(), exit(0));
	else if (ft_strncmp(cmd->argv[0], "unset", INT_MAX) == 0)
		return (unset(cmd->argv, cmd->g_env), exit(0));
	else if (ft_strncmp(cmd->argv[0], "cd", INT_MAX) == 0)
		return (cd(cmd->argv, cmd->g_env), exit(0));
	else if (ft_strncmp(cmd->argv[0], "exit", INT_MAX) == 0)
		return (ft_exit(cmd->argv, cmd->g_env), exit(0));
}

int	ft_isbuiltins(t_node *node)
{
	t_cmd	*cmd;

	if (!node)
		return (0);
	if (node->type != CMD)
		return (0);
	cmd = (t_cmd *)node;
	if (ft_strncmp(cmd->argv[0], "export", INT_MAX) == 0)
		return (export(cmd->argv, cmd->g_env), 1);
	else if (ft_strncmp(cmd->argv[0], "unset", INT_MAX) == 0)
		return (unset(cmd->argv, cmd->g_env), 1);
	else if (ft_strncmp(cmd->argv[0], "cd", INT_MAX) == 0)
		return (cd(cmd->argv, cmd->g_env), 1);
	else if (ft_strncmp(cmd->argv[0], "exit", INT_MAX) == 0)
		return (ft_exit(cmd->argv, cmd->g_env), 1);
	return (0);
}
