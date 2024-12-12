/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:10:24 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/11 14:48:49 by qalpesse         ###   ########.fr       */
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

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		ft_error("");
}

void	ft_stats(int pid)
{
	int	stat;

	stat = 0;
	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		g_exitcode = WEXITSTATUS(stat);
}

void	ft_process(t_node *node, int dupfd, int *pipefd, int *cmd_index)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_error("fork error");
	if (pid == 0)
	{
		if (*cmd_index == 0)
			ft_dup2(pipefd[1], 1);
		if (*cmd_index == -1)
			ft_dup2(dupfd, 0);
		if (*cmd_index > 0)
		{
			ft_dup2(dupfd, 0);
			ft_dup2(pipefd[1], 1);
		}
		close_processfd(pipefd, dupfd);
		ft_exec(node, dupfd, cmd_index);
	}
	if (*cmd_index == -1)
		ft_stats(pid);
}

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
