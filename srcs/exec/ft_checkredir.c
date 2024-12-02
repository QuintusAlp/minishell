/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkredir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:51:47 by qalpesse          #+#    #+#             */
/*   Updated: 2024/11/14 15:22:09 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_checkredir(t_redir *redir)
{
	char cwd[256];
	struct stat f_stat;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
      		perror("getcwd() error");
	if (access(redir->file, F_OK) == -1  && access(ft_strjoin(ft_strjoin(cwd, "/"), redir->file), F_OK) == -1)//
	{
		if (redir->type == HEREDOC || redir->type == I_REDIR)
			ft_panic("No such file or directory", redir->file, 1);
	}
	else
	{
		if (stat(redir->file, &f_stat) == -1)
        	perror("stat error");
		if (redir->type == HEREDOC || redir->type == I_REDIR)
		{
			if (!(f_stat.st_mode & S_IRUSR))
        		ft_panic("Permission denied", redir->file, 1);
		}
		else if (redir->type == O_REDIR_APPEND || redir->type == O_REDIR_TRUNC)
		{
			if (!(f_stat.st_mode & S_IWUSR))
				ft_panic("Permission denied", redir->file, 1);
		}
	}
}
