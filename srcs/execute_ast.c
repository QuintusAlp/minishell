/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:01:11 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/14 11:14:12 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void ft_exec(t_node *node, int *pipefd, int dupfd, int *cmd_index)
{
	if (node->type == PIPE)
		ft_exec_pipe((t_pipe *)node, dupfd, cmd_index);
	if (node->type == CMD)
		ft_exec_cmd((t_cmd *)node, pipefd, dupfd, cmd_index);
}
void	ft_execute_ast(t_node *node)
{
	int pid;
	int	cmd_index;

	pid = fork();
	cmd_index = 0;
	if (pid == -1)
		ft_error("fork");
	if (pid == 0)
	{
		ft_exec(node, NULL, -1,  &cmd_index);
		while (wait(NULL) > 0) ;
	}
	else
		waitpid(pid, NULL, 0);
}

