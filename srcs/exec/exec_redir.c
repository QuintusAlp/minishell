/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:09:30 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/09 11:40:14 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_redir(t_redir *redir, int dupfd, int *cmd_index)
{
	int	fd;

	ft_checkredir(redir);
	if (redir->type == O_REDIR_TRUNC)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_dup2(fd, 1);
	}
	if (redir->type == O_REDIR_APPEND)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		ft_dup2(fd, 1);
	}
	if (redir->type == I_REDIR || redir->type == HEREDOC)
	{
		fd = open(redir->file, O_RDONLY, 0644);
		ft_dup2(fd, 0);
	}
	close(fd);
	ft_exec(redir->cmd, dupfd, cmd_index);
}
