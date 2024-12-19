/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:41:39 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/19 13:33:44 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*need to handle double char as one like >> or &&*/
char	*ft_get_sp_token(char *c, int *i)
{
	char	*data;

	if (*c == *(c + 1))
	{
		data = malloc(3 * sizeof(char));
		if (!data)
			return (NULL);
		data[0] = *c;
		data[1] = *(c + 1);
		data[2] = '\0';
		*i += 1;
		return (data);
	}
	data = malloc(2 * sizeof(char));
	data[0] = *c;
	data[1] = '\0';
	return (data);
}

void	ft_token_type(t_list *token)
{
	while (token)
	{
		if (ft_strcmp(token->value, "|") == 0)
			token->type = PIPE;
		else if (ft_strcmp(token->value, "<") == 0)
			token->type = I_REDIR;
		else if (ft_strcmp(token->value, ">") == 0)
			token->type = O_REDIR_TRUNC;
		else if (ft_strcmp(token->value, ">>") == 0)
			token->type = O_REDIR_APPEND;
		else if (ft_strcmp(token->value, "<<") == 0)
			token->type = HEREDOC;
		else
			token->type = WORD;
		token = token->next;
	}
}

void	ft_verify_quotestatus(int d_quote, int s_quote, t_list **token)
{
	if (d_quote || s_quote)
	{
		ft_lstclear(token, &free);
		g_exitcode = 258;
		ft_error("bash: syntax error quote not close");
	}
}

/*king of split but that work directly 
  with chain list and that keep sep if it has to */
void	ft_lexer(char *str, t_list **tokens)
{
	int		i;
	int		d_quote_status;
	int		s_quote_status;

	i = 0;
	d_quote_status = 0;
	s_quote_status = 0;
	while (str && str[i])
	{
		if (!ft_is_sp(str[i], &d_quote_status, &s_quote_status))
			ft_lstadd_back(tokens,
				ft_lstnew(ft_get_token(&str[i], &i,
						&d_quote_status, &s_quote_status), WORD));
		else
		{
			if (ft_is_sp(str[i], &d_quote_status, &s_quote_status) == 1)
				ft_lstadd_back(tokens,
					ft_lstnew(ft_get_sp_token(&str[i], &i), WORD));
		}
		i ++;
	}
	ft_verify_quotestatus(d_quote_status, s_quote_status, tokens);
	ft_token_type(*tokens);
}
