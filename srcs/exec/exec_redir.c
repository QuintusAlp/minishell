/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:09:30 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/16 17:03:53 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strfind(char *str, char *str_to_find)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != str_to_find[i])
			return (0);
		i++;
	}
	return (1);
}

void	ft_heredoc(t_redir *heredoc)
{
	char	*str;
	int		fd;

	ft_printf("here_doc\n");
	fd = open("/tmp/hd_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("open");
	str = get_next_line(0);
	while (str && !ft_strfind(str, heredoc->file))
	{
		if (write(fd, str, ft_strlen(str)) == -1)
		{
			free(str);
			ft_error("write");
		}
		free(str);
		str = get_next_line(0);
	}
	close(fd);
	fd = open("/tmp/hd_file", O_RDONLY);
	if (dup2(fd, 0) == -1)
		ft_error ("dup2");
	close(fd);
}

void	ft_exec_redir(t_redir *redir, int dupfd, int *cmd_index)
{
	int	fd;

	if (redir->type == O_REDIR_TRUNC)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (dup2(fd, 1) == -1)
			ft_error ("dup2");
	}
	if (redir->type == O_REDIR_APPEND)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (dup2(fd, 1) == -1)
			ft_error ("dup2");
	}
	if (redir->type == I_REDIR)
	{
		fd = open(redir->file, O_RDONLY, 0644);
		if (dup2(fd, 0) == -1)
			ft_error ("dup2");
	}
	if (redir->type == HEREDOC)
		ft_heredoc(redir);
	close(fd);
	ft_exec(redir->cmd, dupfd, cmd_index);
}
