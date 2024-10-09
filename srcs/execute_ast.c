/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:01:11 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/09 14:32:40 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void ft_exec(t_node *node)
{
	if (node->type == PIPE)
		ft_exec_pipe((t_pipe *)node);
	if (node->type == CMD)
		ft_exec_cmd((t_cmd *)node);
}
void	ft_execute_ast(t_node *node)
{
	int pid;

	pid = fork();
	if (pid == -1)
		ft_error("fork");
	if (pid == 0)
		ft_exec(node);
	else
		waitpid(pid, NULL, 0);
}

