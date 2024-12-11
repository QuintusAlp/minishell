/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:04:17 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/11 11:49:35 by qalpesse         ###   ########.fr       */
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
			{
				return (1);
			}
			token = token->next;
		}
	}
	return (0);
}

t_node	*ft_parsetoken(t_list **token, t_env **g_env, int *hd_index, int *exitcode)
{
	int		type;
	t_list	*prev;
	t_list	*next;

	if (ft_lstfind(*token, PIPE))
	{
		prev = ft_get_prevpipe(*token);
		next = ft_get_nextpipe(*token);
		return (ft_pipenode(ft_parsetoken(&prev, g_env, hd_index, exitcode),
				ft_parsetoken(&next, g_env, hd_index, exitcode), token));
	}
	if (ft_lstfind(*token, REDIR))
	{
		prev = ft_get_prevredir(*token);
		return (ft_redirnode(
				ft_get_file_and_type(*token, &type, hd_index, exitcode),
				ft_parsetoken(&prev, g_env, hd_index, exitcode), type, token));
	}
	if (ft_lstfind(*token, WORD))
	{
		return (ft_cmdnode(ft_getargv(*token), g_env, token));
	}
	ft_lstclear(token, &free);
	return (NULL);
}
