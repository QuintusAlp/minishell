/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:10:24 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/14 11:41:00 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//Entrée standard 	stdin 	0
//Sortie standard 	stdout 	1
void	ft_exec_pipe(t_pipe *node, int dupfd, int *cmd_index)
{
	int pipefd[2];
	if (pipe(pipefd) == -1)
		ft_error("pipe");
	ft_exec(node->left, pipefd, dupfd, cmd_index);
	(*cmd_index)++;
	if(dupfd != -1)
		close(dupfd);
	dupfd = dup(pipefd[0]);
	close(pipefd[0]);
	close(pipefd[1]);
	if (node->right->type != PIPE)
	*cmd_index = -1;
	ft_exec(node->right, pipefd, dupfd, cmd_index);
	close(dupfd);
	
	return ;
}
