/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:10:24 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/15 14:35:45 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_processfd(int *pipefd, int dupfd)
{
	close(pipefd[1]);
	close(pipefd[0]);
	if (dupfd != -1)
		close(dupfd);
}

void	ft_process(t_node *node, int dupfd, int *pipefd, int *cmd_index)
{
	int	pid;
	int	dup_value;

	pid = fork();
	if (pid == -1)
		ft_error("fork error");
	if (pid == 0)
	{
		if (*cmd_index == 0)
			dup_value = dup2(pipefd[1], 1);
		if (*cmd_index == -1)
			dup_value = dup2(dupfd, 0);
		if (*cmd_index > 0)
		{
			if (dup2(dupfd, 0) == -1)
				ft_error("dup2 error 2");
			if (dup2(pipefd[1], 1) == -1)
				ft_error("dup2 error 3");
		}
		close_processfd(pipefd, dupfd);
		if (dup_value == -1)
			ft_error("dup2 error");
		ft_exec(node, dupfd, cmd_index);
	}
}

//Entrée standard 	stdin 	0
//Sortie standard 	stdout 	1
void	ft_exec_pipe(t_pipe *node, int dupfd, int *cmd_index)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		ft_error("pipe");
	ft_process(node->left, dupfd, pipefd, cmd_index);
	(*cmd_index)++;
	if (dupfd != -1)
		close(dupfd);
	dupfd = dup(pipefd[0]);
	close(pipefd[0]);
	close(pipefd[1]);
	if (node->right->type != PIPE)
	{
		*cmd_index = -1;
		ft_process(node->right, dupfd, pipefd, cmd_index);
	}
	else
		ft_exec(node->right, dupfd, cmd_index);
	close(dupfd);
	return ;
}
