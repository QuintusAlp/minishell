/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:43:25 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/24 15:07:43 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_printlst(t_list *e)
{
	t_list	*tokens;
	tokens = e;
	while(tokens)
	{
		printf("token value: %s \n", (char *)tokens->value);
		printf("token type: %d \n", tokens->type);
		printf("---------------------------------------\n");
		tokens = tokens->next;
	}
}

void ft_parsing(char *prompt)
{
	t_list *tokens;

	tokens = ft_lexer(prompt);
	ft_printlst(tokens);
	ft_lstclear(&tokens,&free); 

}
