/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:04:17 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/27 15:37:35 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lstfind(t_list *token, int type)
{
    if (!token)
        return (0);
	if (type == REDIR)
	{
		while (token)
		{
			if (ft_token_isredir(token))
				return (1);
			token = token->next;
		}
	}
	else
	{
		while (token)
		{
			if (token->type == type)
				return (1);
			token = token->next;
		}
	}
	return (0);
}

t_node	*ft_parsetoken(t_list **token, char **env, int *hd_index)
{
	int	type;
	t_list	*prev;
	t_list	*next;

	if (ft_lstfind(*token, PIPE))
	{
		prev = ft_get_prevpipe(*token);
		next = ft_get_nextpipe(*token);
		return (ft_pipenode(ft_parsetoken(&prev, env, hd_index),
				ft_parsetoken(&next, env, hd_index), token));
	}
	if (ft_lstfind(*token, REDIR))
	{
		prev = ft_get_prevredir(*token);
		return (ft_redirnode(ft_get_file_and_type(*token, &type, hd_index, env),
                    ft_parsetoken(&prev, env, hd_index), type, token));
	}
	if (ft_lstfind(*token, WORD))
	{
		return (ft_cmdnode(ft_getargv(*token), env, token));
	}
	ft_lstclear(token, &free);
	return (NULL);
}
//////////////AST PRINTER///////////////////////////////////
void ast_printer(t_node *node, int level);

// Helper function to print indentation based on tree level
void print_indent(int level)
{
    for (int i = 0; i < level; i++)
        printf("    ");
}

// AST printer for t_cmd nodes
void print_cmd(t_cmd *cmd, int level)
{
    print_indent(level);
    printf("CMD: ");
    for (int i = 0; cmd->argv[i]; i++)
        printf("%s ", cmd->argv[i]);
    printf("\n");
}

// AST printer for t_redir nodes
void print_redir(t_redir *redir, int level)
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
void print_pipe(t_pipe *pipe_node, int level)
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
void ast_printer(t_node *node, int level)
{
    if (!node)
        return;

    switch (node->type)
    {
    case CMD:
        print_cmd((t_cmd *)node, level);
        break;
    case I_REDIR:
    case O_REDIR_APPEND:
    case O_REDIR_TRUNC:
    case HEREDOC:
        print_redir((t_redir *)node, level);
        break;
    case PIPE:
        print_pipe((t_pipe *)node, level);
        break;
    default:
        print_indent(level);
        printf("Unknown node type\n");
    }
}
/////////////////////////////////////////
