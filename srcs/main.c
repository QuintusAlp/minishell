/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:58:39 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/23 11:42:31 by qalpesse         ###   ########.fr       */
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

void ft_pars_and_exec(char *prompt, char **env)
{
	t_list *tokens;
	t_node *ast;

	if (!prompt)
		return ;
	tokens = NULL;
	ast = NULL;
	ft_lexer(prompt, &tokens);
	//ft_printlst(tokens);
	ast = ft_parsetoken(&tokens, env);
	//ast_printer(ast, 0);
	ft_execute_ast(ast);
	ft_free_ast(ast);
	//system("leaks minishell");
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char	*prompt;

	prompt = readline("\033[1;92mminishell$\033[0m ");
	while (prompt)
	{
		if (*prompt)
			ft_pars_and_exec(prompt, env);
		free(prompt);
		prompt = readline("\033[1;92mminishell$\033[0m ");
	}
	return (0);
}
