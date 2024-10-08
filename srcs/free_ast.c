/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:41:50 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/08 14:28:49 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_pipe(t_node *node, void (*ft_free_ast)(t_node *))
{
	t_pipe *pipe = (t_pipe *)node;
	ft_free_ast(pipe->left);
	ft_free_ast(pipe->right);
	free(pipe);
}

void	ft_free_redir(t_node *node, void (*ft_free_ast)(t_node *))
{
	t_redir	*redir = (t_redir*)node;
	ft_free_ast(redir->cmd);
	free(redir->file);
}
void	ft_freeargv(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
}
void	ft_free_cmd(t_node *node)
{
	t_cmd	*cmd= (t_cmd*)node;
	ft_freeargv(cmd->argv);
	ft_freeargv(cmd->env);
}
void	ft_free_ast(t_node *node)
{
	if (node->type == PIPE)
		return(ft_free_pipe(node, &ft_free_ast));
	if (node->type == I_REDIR
		|| node->type == O_REDIR_APPEND
		|| node->type == O_REDIR_TRUNC
		|| node->type == HEREDOC)
		return(ft_free_redir(node, &ft_free_ast));
	if(node->type == CMD)
		return (ft_free_cmd(node));
}
