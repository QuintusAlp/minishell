/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:09:30 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/24 18:36:43 by qalpesse         ###   ########.fr       */
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
	// struct stat f_stat;

	// printf("redir\n");
	// if (stat(redir->file, &f_stat) == -1)
    //     perror("stat");
	// printf("mode: %d\n", (f_stat.st_mode & S_IRUSR));
	// if ((f_stat.st_mode & S_IRUSR))
    //     printf("read \n");
    // if (f_stat.st_mode & S_IWUSR)
    //     printf("write \n");
    // if (f_stat.st_mode & S_IXUSR)
    //     printf("execute \n");
	
	if (!redir->file)
		ft_panic("syntax error near token", NULL, 1);
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
		if (getcwd(cwd, sizeof(cwd)) == NULL)
      		perror("getcwd() error");
		// if (redir->type == I_REDIR)
		// {
		// 	if (access(redir->file, X_OK) && access(ft_strjoin(cwd, redir->file), X_OK))
		// 		ft_panic("No such file or directory", redir->file, 1);
		// }
		fd = open(redir->file, O_RDONLY, 0644);
		ft_dup2(fd, 0);
	}
	close(fd);
	ft_exec(redir->cmd, dupfd, cmd_index);
}
