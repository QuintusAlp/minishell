/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:41:39 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/24 19:34:27 by qalpesse         ###   ########.fr       */
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
	printf("new token\n");
	*d_quote = 0;
	*s_quote = 0;
	while (ft_update_quotes_status(s[j], d_quote, s_quote), s[j] && !ft_is_sp(s[j], d_quote, s_quote) )
	{
		j++;
	}
	data = malloc((j + 1) * sizeof(char));
	j = 0;
	*d_quote = 0;
	*s_quote = 0;
	printf("add token in data\n");
	while (ft_update_quotes_status(s[j], d_quote, s_quote), s[j] && !ft_is_sp(s[j], d_quote, s_quote))
	{
		data[j] = s[j];
		j++;
	}
	data[j] = '\0';
	*i += j - 1;
	return (data);
}
char *ft_get_sp_token(char c)
{
	char *data;

	data = malloc(2 * sizeof(char));
	data[0] = c;
	data[1] = '\0';
	return (data);
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
		{
			ft_lstadd_back(&tokens, ft_lstnew(ft_get_token(&str[i], &i, &d_quote_status, &s_quote_status), WORD));
		}
		else
		{
			if (ft_is_sp(str[i], &d_quote_status, &s_quote_status) == 1)
				ft_lstadd_back(&tokens, ft_lstnew(ft_get_sp_token(str[i]), WORD));
		}
		i++;
	}
	if (d_quote_status || s_quote_status)
		ft_error("quote not close");
	return (tokens);
}
