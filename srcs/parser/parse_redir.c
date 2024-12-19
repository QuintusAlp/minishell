/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:26:20 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/19 15:55:35 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*ft_redirnode(char *file, t_node *cmd, int type, t_list **token)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	redir->type = type;
	redir->cmd = cmd;
	redir->file = file;
	ft_lstclear(token, &free);
	return ((t_node *)redir);
}

int	ft_token_isredir(t_list *token)
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
	t_list	*tokens;

	tokens = token->next;
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
	while (!ft_token_isredir(token))
	{
		ft_lstadd_back(&prev, ft_lstnew(ft_strdup(token->value), token->type));
		token = token->next;
	}
	token = token->next;
	if (token && token-> type == WORD)
		token = token->next;
	while (token)
	{
		ft_lstadd_back(&prev, ft_lstnew(ft_strdup(token->value), token->type));
		token = token->next;
	}
	return (prev);
}

char	*ft_get_file_and_type(t_list *token, int *type,
		int *hd_index, t_env **g_env)
{
	char	*hd_file;
	char	*index;
	int		pid;

	while (!ft_token_isredir(token))
		token = token->next;
	*type = token->type;
	token = token->next;
	if (*type == HEREDOC)
	{
		index = ft_itoa(*hd_index);
		hd_file = ft_strjoin("/tmp/hd_file", index);
		free(index);
		(*hd_index)--;
		ft_set_sig(2);
		pid = fork();
		if (pid == 0)
		{
			ft_heredoc(token->value, hd_file, g_env);
			exit(0);
		}
		ft_stats(pid);
		return (hd_file);
	}
	return (ft_strdup(token->value));
}
