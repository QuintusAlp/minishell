/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:04:17 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/06 14:30:59 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//ast functions
// pipe
t_list	*ft_get_prevpipe(t_list *token);
t_list	*ft_get_nextpipe(t_list *token);
t_node	*ft_pipenode(t_node *left, t_node *right);
// redir
t_node	*ft_redirnode(t_node *cmd, char *file, int	type);
t_list *ft_get_prevredir(t_list *token);
char *ft_get_file(t_list *token);
// cmd
t_node	*ft_cmdnode(char **argv, char **env);
char **ft_getargv(t_list *token);

int	ft_lstfind(t_list *token, int type)
{
	while(token)
	{
		if (token->type == type)
			return (1);
		token = token->next;
	}
	return (0);
}

t_node	*ft_parsetoken(t_list *token)
{
	ft_printlst(token);
	printf("||||||||||||||||||\n");
	if (token->type == PIPE)
		return (ft_error("syntax error, pipe first token"), NULL);

	if (ft_lstfind(token, PIPE))
		return (ft_pipenode(ft_parsetoken(ft_get_prevpipe(token)),
				ft_parsetoken(ft_get_nextpipe(token))));

	if (ft_lstfind(token, I_REDIR))
		return (ft_redirnode(ft_parsetoken(ft_get_prevredir(token)), ft_get_file(token), I_REDIR));
	if (ft_lstfind(token, O_REDIR_APPEND))
		return (ft_redirnode(ft_parsetoken(ft_get_prevredir(token)), ft_get_file(token), O_REDIR_APPEND));
	if (ft_lstfind(token, O_REDIR_TRUNC))
		return (ft_redirnode(ft_parsetoken(ft_get_prevredir(token)), ft_get_file(token), O_REDIR_TRUNC));
	if (ft_lstfind(token, HEREDOC))
		return (ft_redirnode(ft_parsetoken(ft_get_prevredir(token)), ft_get_file(token), HEREDOC));

	if (ft_lstfind(token, WORD))
			return (ft_cmdnode(ft_getargv(token), NULL));
	return (NULL);
}

void	*ft_ast_builder(t_list *token)
{
	t_node	*ast;
	
	ast = ft_parsetoken(token);
	return (NULL);
}
