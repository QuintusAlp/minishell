/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:41:39 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/03 17:38:22 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_update_quotes_status(char c, int *d_quote_status, int *s_quote_status)
{
	if (c == '\'')
	{
		if (!(*d_quote_status))
		{
			if (!(*s_quote_status))
				*s_quote_status = 1;
			else
				*s_quote_status = 0;
		}
	}
	if (c == '\"')
	{
		if (!(*s_quote_status))
		{
			if (!(*d_quote_status))
				*d_quote_status = 1;
			else
				*d_quote_status = 0;
		}
	}
}

int	ft_is_sp(char c, int *d_quote, int *s_quote)
{
	if (*d_quote || *s_quote)
		return (0);
	if (c == '>' || c == '<')
		return (1);
	if (c == '|')
		return (1);
	if (c == ' ')
		return (2);
	return (0);
}
char *ft_get_token(char *s, int *i, int *d_quote, int *s_quote)
{
	int		j;
	char	*data;

	j = 0;
	*d_quote = 0;
	*s_quote = 0;
	while (ft_update_quotes_status(s[j], d_quote, s_quote), s[j] && !ft_is_sp(s[j], d_quote, s_quote) )
		j++;
	data = malloc((j + 1) * sizeof(char));
	j = 0;
	*d_quote = 0;
	*s_quote = 0;
	while (ft_update_quotes_status(s[j], d_quote, s_quote), s[j] && !ft_is_sp(s[j], d_quote, s_quote))
	{
		data[j] = s[j];
		j++;
	}
	data[j] = '\0';
	*i += j - 1;
	return (data);
}
/*need to handle fouble char as one like >> or &&*/
char *ft_get_sp_token(char *c, int *i)
{
	char *data;

	if (*c == *(c + 1))
	{
		data = malloc(3 * sizeof(char));
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
void	ft_token_type(t_list *tokens)
{
	while (tokens)
	{
		if ()
		tokens = tokens->next
	}	
}
/*king of split but that work directly with chain list and that keep sep if it has to */
t_list *ft_lexer(char *str)
{
	int	i;
	t_list *tokens;
	int	d_quote_status;
	int	s_quote_status;

	i = 0;
	tokens = NULL;
	d_quote_status = 0;
	s_quote_status = 0;
	while (str[i])
	{
		if (!ft_is_sp(str[i], &d_quote_status, &s_quote_status))
			ft_lstadd_back(&tokens, ft_lstnew(ft_get_token(&str[i], &i, &d_quote_status, &s_quote_status), WORD));
		else
		{
			if (ft_is_sp(str[i], &d_quote_status, &s_quote_status) == 1)
				ft_lstadd_back(&tokens, ft_lstnew(ft_get_sp_token(&str[i], &i), WORD));
		}
		i++;
	}
	if (d_quote_status || s_quote_status)
	{
		ft_lstclear(&tokens,&free); 
		ft_error("quote not close");
	}
	ft_token_type(tokens);
	return (tokens);
}
