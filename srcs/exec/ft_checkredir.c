/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkredir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:51:47 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/09 12:22:19 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_re(t_redir *redir)
{
	struct stat	f_stat;

	if (stat(redir->file, &f_stat) == -1)
		perror("stat error");
	if (redir->type == HEREDOC || redir->type == I_REDIR)
	{
		if (!(f_stat.st_mode & S_IRUSR))
			return (0);
	}
	else if (redir->type == O_REDIR_APPEND || redir->type == O_REDIR_TRUNC)
	{
		if (!(f_stat.st_mode & S_IWUSR))
			return (0);
	}
	return (1);
}

void	ft_checkredir(t_redir *redir)
{
	char			cwd[256];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	if (access(redir->file, F_OK) == -1
		&& access(ft_strjoin(ft_strjoin(cwd, "/"),
				redir->file), F_OK) == -1)
	{
		if (redir->type == HEREDOC || redir->type == I_REDIR)
			ft_panic("No such file or directory", redir->file, 1);
	}
	else
	{
		if (!ft_check_re(redir))
			ft_panic("Permission denied", redir->file, 1);
	}
}
