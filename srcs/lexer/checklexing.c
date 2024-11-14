/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checklexing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:58:04 by qalpesse          #+#    #+#             */
/*   Updated: 2024/11/14 14:14:39 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_tokenerror(char *str, char *u_token)
{
	write(2, str,ft_strlen(str));
	write(2, "`", 1);
	write(2, u_token, ft_strlen(u_token));
	write(2, "\'", 1);
	write(2, "\n", 1);
}
int ft_checklexing(t_list *token)
{
	if (token && token->type == PIPE)
	{
		g_exitcode = 258;
		ft_tokenerror("bash: syntax error near unexpected token", token->value);
		return (1);
	}
	while (token)
	{
		if (token->type >= I_REDIR && token->type <= HEREDOC)
		{
			if (!token->next)
			{
				g_exitcode = 258;
				ft_tokenerror("bash: syntax error near unexpected token", "newline");
				return (1);
			}
			if ((token->next)->type != WORD)
			{
				g_exitcode = 258;
				ft_tokenerror("bash: syntax error near unexpected token", (token->next)->value);
				return (1);
			}
		}
		token = token->next;
	}
	return (0);
}
