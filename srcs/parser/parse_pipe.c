/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:26:09 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/18 18:37:00 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*ft_pipenode(t_node *left, t_node *right, t_list **token)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	pipe->type = PIPE;
	pipe->left = left;
	pipe->right = right;
	ft_lstclear(token, &free);
	return ((t_node *)pipe);
}

t_list	*ft_get_prevpipe(t_list *token)
{
	t_list	*prev;

	prev = NULL;
	while (token && token->type != PIPE)
	{
		ft_lstadd_back(&prev, ft_lstnew(ft_strdup(token->value), token->type));
		token = token->next;
	}
	return (prev);
}

t_list	*ft_get_nextpipe(t_list *token)
{
	t_list	*next;
	// char *buffer;

	next = NULL;
	while (token && token->type != PIPE)
		token = token->next;
	token = token->next;
	// if (!token)
	// {
	// 	while(1)
	// 	{
	// 		buffer = readline("> ");
	// 		if (!buffer || buffer[0] != '\0')
	// 			break ;
	// 	}
	// 	if (buffer)
	// 	{
	// 		ft_lexer(buffer, &next);
	// 		return (next);
	// 	}
	// 	return (NULL);
	// }
	while (token)
	{
		ft_lstadd_back(&next, ft_lstnew(ft_strdup(token->value), token->type));
		token = token->next;
	}
	return (next);
}
