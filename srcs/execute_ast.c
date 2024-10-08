/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:01:11 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/08 22:12:37 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//PIPE//////////////////////////////////////////////////////////
void	first_child_process(t_node *left)
{
	(void)left;
	printf("first child\n");
	//ft_execute_ast(left);
}

void	second_child_process(t_node *right)
{
	(void)right;
	printf("second child\n");
	//ft_execute_ast(right);
}

void	ft_exec_pipe(t_pipe *node)
{
	int	pids[2];

	pids[0] = fork();
	if (pids[0] == -1)
		ft_error("fork");
	if (pids[0] == 0)
		first_child_process(node->left);
	pids[1] = fork();
	if (pids[1] == -1)
		ft_error("fork");
	if (pids[1] == 0)
		second_child_process(node->right);
	while(wait(NULL))
		;
}
///////////////////////////////////////////////////////
void	ft_exec_cmd(t_cmd *cmd)
{
	printf("cmd: %s\n", cmd->argv[0]);
}
void	ft_execute_ast(t_node *node)
{
	//printf("execute ast\n");
	if (node->type == PIPE)
		ft_exec_pipe((t_pipe *)node);
	if (node->type == CMD)
		ft_exec_cmd((t_cmd *)node);

}

