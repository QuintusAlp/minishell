/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:26:20 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/07 12:43:30 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*ft_redirnode(t_node *cmd, char *file, int type, t_list *token)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	redir->type = type;
	redir->cmd = cmd;
	redir->file = file;
	return (ft_lstclear(&token, &free), (t_node *)redir);
}
int ft_token_isredir(t_list *token)
{
	if (!token)
		return (0);
	if (token->type == I_REDIR || token->type == HEREDOC)
		return (1);
	if (token->type == O_REDIR_APPEND || token->type == O_REDIR_TRUNC)
		return (1);
	return (0);
}
int	ft_check_other_redir(t_list *token)
{
	t_list 		*tokens = token->next;
	while (tokens)
	{
		if (ft_token_isredir(tokens))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
t_list	*ft_get_prevredir(t_list *token)
{
	t_list	*prev;

	prev = NULL;
	while (!(ft_token_isredir(token) && !ft_check_other_redir(token)))
	{
		ft_lstadd_back(&prev, ft_lstnew(token->value, token->type));
		token = token->next;
	}
	return (prev);
}
char *ft_get_file(t_list *token)
{
	t_list *start_lst;

	start_lst = token;
	while (!(ft_token_isredir(token) && !ft_check_other_redir(token)))
		token = token->next;
	if ((token->next)->type == WORD)
	{
		return (ft_strdup((token->next)->value));
	}
	else
		return (ft_printf("file not fouhnd\n"), NULL);
	return (NULL);
}