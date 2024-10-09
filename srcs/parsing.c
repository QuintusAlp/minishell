/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:43:25 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/09 15:54:16 by qalpesse         ###   ########.fr       */
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

void ft_pars_and_exec(char *prompt, char **env)
{
	t_list *tokens;
	t_node *ast;

	if (!prompt)
		return ;
	tokens = ft_lexer(prompt);
	ast = ft_parsetoken(tokens, env);
	//ast_printer(ast, 0);
	ft_execute_ast(ast);
	ft_free_ast(ast);
	// ft_printlst(tokens);

}
