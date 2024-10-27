/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:09:30 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/27 12:02:17 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


//file permission: rwx : 
// valeurs octals:
// x: 1
// w: 2
// r: 4
void	ft_exec_redir(t_redir *redir, int dupfd, int *cmd_index)
{
	int	fd;
	char cwd[256];
	struct stat f_stat;

	if (stat(redir->file, &f_stat) == -1)
        perror("stat");
    if (f_stat.st_mode & S_IXUSR)
        printf("execute \n");
	if (ft_strcmp(redir->file, "\n"))
		ft_panic("syntax error near unexpected token `newline'", NULL, 258);
	if (redir->type == O_REDIR_TRUNC)
	{
		if (!(f_stat.st_mode & S_IWUSR))
			ft_panic("Permission denied", redir->file, 1);
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_dup2(fd, 1);
	}
	if (redir->type == O_REDIR_APPEND)
	{
		if (!(f_stat.st_mode & S_IWUSR))
			ft_panic("Permission denied", redir->file, 1);
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		ft_dup2(fd, 1);
	}
	if (redir->type == I_REDIR || redir->type == HEREDOC)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
      		perror("getcwd() error");
		if (!(f_stat.st_mode & S_IRUSR))
        		ft_panic("Permission denied", redir->file, 1);
		if (!access(redir->file, X_OK)  && !access(ft_strjoin(ft_strjoin(cwd, "/"), redir->file), X_OK))//
			ft_panic("No such file or directory", redir->file, 1);
		
		fd = open(redir->file, O_RDONLY, 0644);
		ft_dup2(fd, 0);
	}
	close(fd);
	ft_exec(redir->cmd, dupfd, cmd_index);
}
