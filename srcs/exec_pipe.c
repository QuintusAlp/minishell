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

#include "../includes/minishell.h"

//Entrée standard 	stdin 	0
//Sortie standard 	stdout 	1
void	ft_exec_pipe(t_pipe *node, int dupfd, int *cmd_index)
{
	int	pid1;
	int	pid2;
	int pipefd[2];

	if (pipe(pipefd) == -1)
		ft_error("pipe");
	pid1 = fork();
	if (pid1 == -1)
		ft_error("fork error");
	if (pid1 == 0)
	{
		if (*cmd_index == 0)
		{
			if (dup2(pipefd[1], 1) == -1)
					ft_error("dup2 error 1");
		}
		if (*cmd_index == -1)
		{
			if (dup2(dupfd, 0) == -1)
					ft_error("dup2 error 2");
		}
		if (*cmd_index > 0)
		{
			if (dup2(dupfd, 0) == -1)
				ft_error("dup2 error 2");
			if (dup2(pipefd[1], 1) == -1)
				ft_error("dup2 error 3");
		}
		close(pipefd[1]);
		close(pipefd[0]);
		if (dupfd != -1)
			close(dupfd);
		ft_exec(node->left, pipefd, dupfd, cmd_index);
	}
	(*cmd_index)++;
	if(dupfd != -1)
		close(dupfd);
	dupfd = dup(pipefd[0]);
	close(pipefd[0]);
	close(pipefd[1]);
	if (node->right->type != PIPE)
	{
		*cmd_index = -1;
		pid2 = fork();
		if (pid2 == -1)
			ft_error("fork error");
		if (pid2 == 0)
		{
			if (*cmd_index == 0)
			{
				if (dup2(pipefd[1], 1) == -1)
						ft_error("dup2 error 1");
			}
			if (*cmd_index == -1)
			{
				if (dup2(dupfd, 0) == -1)
						ft_error("dup2 error 2");
			}
			if (*cmd_index > 0)
			{
				if (dup2(dupfd, 0) == -1)
					ft_error("dup2 error 2");
				if (dup2(pipefd[1], 1) == -1)
					ft_error("dup2 error 3");
			}
			close(pipefd[1]);
			close(pipefd[0]);
			if (dupfd != -1)
				close(dupfd);
			ft_exec(node->right, pipefd, dupfd, cmd_index);
		}
	}
	else
		ft_exec(node->right, pipefd, dupfd, cmd_index);
	close(dupfd);
	
	return ;
}

