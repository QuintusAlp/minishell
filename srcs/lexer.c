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

int	ft_is_sp(char c)
{
	if (c == '>' || c == '<')
		return (1);
	if (c == '|')
		return (1);
	if (c == ' ' || c == '\0')
		return (2);
	return (0);
}

t_list *ft_lexer(char *str)
{
	int	i;
	int	j;
	char *data;
	t_list *tokens;

	i = 0;
	j = 0;
	tokens = NULL;
	while (str[i])
	{
		if (!ft_is_sp(str[i]))
		{
			j = 0;
			while (!ft_is_sp(str[i + j]))
				j++;
			data = malloc((j + 1) * sizeof(char));
			j = -1;
			while (j++, !ft_is_sp(str[i + j]))
				data[j] = str[i + j];
			data[j] = '\0';
			ft_lstadd_back(&tokens, ft_lstnew(data, WORD));
			i += j - 1;
		}
		else
		{
			if (ft_is_sp(str[i]) == 1)
			{
				data = malloc(2 * sizeof(char));
				data[0] = str[i];
				data[1] = '\0';
				ft_lstadd_back(&tokens, ft_lstnew(data, WORD));
			}
		}
		i++;
	}
	return (tokens);
}
