/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:09:30 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/23 14:31:08 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strfind(char *str, char *str_to_find)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while ((str[i] && str[i] != '\n') || str_to_find[i])
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

	fd = open("/tmp/hd_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("open");
	str = readline("> ");
	while (!ft_strfind(str, heredoc->file))
	{
		if (write(fd, str, ft_strlen(str)) == -1)
		{
			free(str);
			ft_error("write");
		}
		free(str);
		str = readline("> ");
	}
	write(fd, "\n", 1);
	close(fd);
}

void	ft_exec_redir(t_redir *redir, int dupfd, int *cmd_index)
{
	int	fd;
	char cwd[256];

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
	if (redir->type == I_REDIR)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
      		perror("getcwd() error");
		if (access(redir->file, X_OK) && access(ft_strjoin(cwd, redir->file), X_OK))
			ft_panic("No such file or directory", redir->file, 1);
		fd = open(redir->file, O_RDONLY, 0644);
		ft_dup2(fd, 0);
	}
	if (redir->type == HEREDOC)
	{
		ft_heredoc(redir);
		fd = open("/tmp/hd_file", O_RDONLY,  0644);
		ft_dup2(fd, 0);
	}
	close(fd);
	ft_exec(redir->cmd, dupfd, cmd_index);
}
