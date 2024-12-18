/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checklexing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:58:04 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/18 18:43:10 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	terr(char *str, char *u_token)
{
	write(2, str, ft_strlen(str));
	write(2, "`", 1);
	write(2, u_token, ft_strlen(u_token));
	write(2, "\'", 1);
	write(2, "\n", 1);
}

int	ft_checklexing(t_list *token)
{
	char *buffer;
	t_list	*next;
	if (token && token->type == PIPE)
	{
		g_exitcode = 258;
		terr("bash: syntax error near unexpected token", token->value);
		return (1);
	}
	while (token)
	{
		if (token->type >= I_REDIR && token->type <= HEREDOC)
		{
			if (!token->next)
			{
				terr("bash: syntax error near unexpected token", "newline");
				return (g_exitcode = 258, 1);
			}
			if ((token->next)->type != WORD)
			{
				terr("bash: syntax error near unexpected token",
					(token->next)->value);
				return (g_exitcode = 258, 1);
			}
		}
		if (token->type == PIPE)
		{
			if (token->next == NULL)
			{
				while(1)
				{
					buffer = readline("> ");
					if (!buffer || buffer[0] != '\0')
						break ;
				}
				if (buffer)
				{
					printf("buffer: %s\n", buffer);
					ft_lexer(buffer, &next);
					printf("okok\n");
					
					token->next = next;
				}
				else
					return (1);
			}
		}
		token = token->next;
	}
	return (0);
}
