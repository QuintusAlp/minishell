/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:27:09 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/09 12:27:33 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//////////////AST PRINTER///////////////////////////////////
void	ast_printer(t_node *node, int level);

// Helper function to print indentation based on tree level
void	print_indent(int level)
{
	for (int i = 0; i < level; i++)
		printf("    ");
}

// AST printer for t_cmd nodes
void	print_cmd(t_cmd *cmd, int level)
{
	print_indent(level);
	printf("CMD: ");
	for (int i = 0; cmd->argv[i]; i++)
		printf("%s ", cmd->argv[i]);
	printf("\n");
}

// AST printer for t_redir nodes
void	print_redir(t_redir *redir, int level)
{
	print_indent(level);
	if (redir->type == I_REDIR)
		printf("INPUT REDIR: %s\n", redir->file);
	else if (redir->type == O_REDIR_APPEND)
		printf("APPEND OUTPUT: %s\n", redir->file);
	else if (redir->type == O_REDIR_TRUNC)
		printf("OUTPUT REDIR: %s\n", redir->file);
	else if (redir->type == HEREDOC)
		printf("HEREDOC: %s\n", redir->file);
	// Recursively print the command inside the redirection
	ast_printer(redir->cmd, level + 1);
}

// AST printer for t_pipe nodes
void	print_pipe(t_pipe *pipe_node, int level)
{
	print_indent(level);
	printf("PIPE:\n");
	// Print the left and right sides of the pipe
	print_indent(level + 1);
	printf("LEFT:\n");
	ast_printer(pipe_node->left, level + 2);
	print_indent(level + 1);
	printf("RIGHT:\n");
	ast_printer(pipe_node->right, level + 2);
}

// Main recursive AST printer
void	ast_printer(t_node *node, int level)
{
	if (!node)
		return ;
	switch (node->type)
	{
	case CMD:
		print_cmd((t_cmd *)node, level);
		break ;
	case I_REDIR:
	case O_REDIR_APPEND:
	case O_REDIR_TRUNC:
	case HEREDOC:
		print_redir((t_redir *)node, level);
		break ;
	case PIPE:
		print_pipe((t_pipe *)node, level);
		break ;
	default:
		print_indent(level);
		printf("Unknown node type\n");
	}
}
/////////////////////////////////////////