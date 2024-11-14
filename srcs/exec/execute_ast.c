/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:01:11 by qalpesse          #+#    #+#             */
/*   Updated: 2024/11/14 15:53:12 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec(t_node *node, int dupfd, int *cmd_index)
{
	if (node->type == PIPE)
		ft_exec_pipe((t_pipe *)node, dupfd, cmd_index);
	if (node->type == CMD)
		ft_exec_cmd((t_cmd *)node);
	if (node->type >= I_REDIR && node->type <= HEREDOC)
		ft_exec_redir((t_redir *)node, dupfd, cmd_index);
}
int ft_check_isbuiltin(t_node *node)
{
	char cwd[256];
	struct stat f_stat;
	t_redir *redir;

	while (node && node->type >= I_REDIR && node->type <= HEREDOC)
	{
		redir = (t_redir *)node;
		if (getcwd(cwd, sizeof(cwd)) == NULL)
      		perror("getcwd() error");
		if (access(redir->file, F_OK) == -1  && access(ft_strjoin(ft_strjoin(cwd, "/"), redir->file), F_OK) == -1)
		{
			if (redir->type == HEREDOC || redir->type == I_REDIR)
				return (0);
		}
		else
		{
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
		}
		node = redir->cmd;
	}
	if (!ft_isbuiltins(node))
		return (0);
	return (1);
	
}
void	ft_execute_ast(t_node *node)
{
	int	pid;
	int	cmd_index;

	if (!node)
		return ;
	if(ft_check_isbuiltin(node))
	{	
		return ;
	}
	pid = fork();
	cmd_index = 0;
	if (pid == -1)
		ft_error("fork");
	if (pid == 0)
	{
		ft_exec(node, -1, &cmd_index);
		while (wait(NULL) > 0)
			;
	}
	else
	{
		int stat = 0;
		waitpid(pid, &stat, 0);
		if (node->type != PIPE)
		{
			if (WIFEXITED(stat))
          	{ 
				g_exitcode =  WEXITSTATUS(stat);
			}
		}
	}
}
