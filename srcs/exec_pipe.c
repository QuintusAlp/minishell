/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:10:24 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/09 16:06:52 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	first_child_process(t_node *left, int *pipefd)
{
	close (1);
	if (dup(pipefd[1]) == -1)
		ft_error("error dup pipefd 1");
	close(pipefd[0]);
	close(pipefd[1]);
	ft_exec(left);
}

void	second_child_process(t_node *right, int *pipefd)
{
	close (0);
	if (dup(pipefd[0]) == -1)
		ft_error("error dup pipefd 0");
	close(pipefd[0]);
	close(pipefd[1]);
	ft_exec(right);
}
//Entrée standard 	stdin 	0
//Sortie standard 	stdout 	1
void	ft_exec_pipe(t_pipe *node)
{
	int	pid1;
	int	pid2;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		ft_error("pipe");
	pid1 = fork();
	if (pid1== -1)
		ft_error("fork");
	if (pid1 == 0)
	{
		if (dup2(pipefd[1], 1) == -1)
			ft_error("error dup pipefd 0");
		close(pipefd[0]);
		close(pipefd[1]);
		ft_exec(node->left);

	}
	
	pid2 = fork();
	if (pid2== -1)
		ft_error("fork");
	if (pid2 == 0)
	{
		if (dup2(pipefd[0], 0) == -1)
			ft_error("error dup pipefd 1");
		close(pipefd[0]);
		close(pipefd[1]);
		ft_exec(node->right);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
	// while(wait(NULL) > 0)
	// 	;
	// waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);
	
}
