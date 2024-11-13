/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:01:11 by qalpesse          #+#    #+#             */
/*   Updated: 2024/11/13 22:27:03 by qalpesse         ###   ########.fr       */
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

	
	while (node->type >= I_REDIR && node->type <= HEREDOC)
	{
		t_redir *redir = (t_redir *)node;
		
		
		
		if (redir->type == O_REDIR_TRUNC)
		{
			if (stat(redir->file, &f_stat) == -1)
       		 	perror("stat");
			if (!(f_stat.st_mode & S_IWUSR))
			{
				printf("test\n");
				g_exitcode = 1;
				return (1);
			}
		}
		printf("redir: %s\n", redir->file);
		if (redir->type == O_REDIR_APPEND)
		{
			if (stat(redir->file, &f_stat) == -1)
       			perror("stat");
			if (!(f_stat.st_mode & S_IWUSR))
				g_exitcode = 1;
				return (1);
		}
		if (redir->type == I_REDIR || redir->type == HEREDOC)
		{
			
			if (getcwd(cwd, sizeof(cwd)) == NULL)
			{
				g_exitcode = 1;
				return (1);
			}
			if (!access(redir->file, X_OK)  && !access(ft_strjoin(ft_strjoin(cwd, "/"), redir->file), X_OK))//
			{
				g_exitcode = 1;
				return (1);
			}
			if (stat(redir->file, &f_stat) == -1)
       		{
				g_exitcode = 1;
				return (1);
			}
			if (!(f_stat.st_mode & S_IRUSR))
			{
				g_exitcode = 1;
				return (1);
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
				printf("exit without pipe\n");
				g_exitcode =  WEXITSTATUS(stat);
			}
		}
	}
}
