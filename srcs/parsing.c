/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:43:25 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/07 15:32:48 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_printlst(t_list *e)
{
	t_list	*tokens;
	tokens = e;
	printf("printlst %p\n", e);
	while(tokens)
	{
		printf("token value: %s %p\n", (char *)tokens->value, tokens->value);
		printf("token type: %d %p\n", tokens->type, tokens);
		printf("---------------------------------------\n");
		tokens = tokens->next;
	}
}

void ft_parsing(char *prompt)
{
	t_list *tokens;

	tokens = ft_lexer(prompt);
	ft_ast_builder(tokens);
	// ft_printlst(tokens);

}
