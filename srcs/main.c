/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:58:39 by qalpesse          #+#    #+#             */
/*   Updated: 2024/11/09 15:30:25 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	char	*readline(const char *prompt);
*/

void	ft_printlst(t_list *e)
{
	t_list	*tokens;
	tokens = e;
	while(tokens)
	{
		dprintf(2,"token value: %s \n", (char *)tokens->value);
		dprintf(2, "token type: %d \n", tokens->type);
		dprintf(2, "---------------------------------------\n");
		tokens = tokens->next;
	}
}

int	ft_countheredocs(t_list *token)
{
	int	nbr_heredocs;

	nbr_heredocs = 0;
	while (token)
	{
		if(token->type == HEREDOC)
			nbr_heredocs ++;
		token = token->next;
	}
	return (nbr_heredocs);
}

void	ft_del_hdfiles(int nbr_heredoc)
{
	char *file;
	char *index;

	while (nbr_heredoc)
	{
		index = ft_itoa(nbr_heredoc);
		file = ft_strjoin("/tmp/hd_file", index);
		unlink(file);
		free(file);
		free(index);
		nbr_heredoc --;
	}
}

void ft_pars_and_exec(char *prompt, char **env)
{
	t_list *tokens;
	t_node *ast;
	int		nbr_heredoc;
	int		nbr_heredoc_bis;
	(void)env;
	if (!prompt)
		return ;
	tokens = NULL;
	ast = NULL;
	ft_lexer(prompt, &tokens);
	trim_tokens(tokens); // TO DO
	//ft_printlst(tokens);
	nbr_heredoc = ft_countheredocs(tokens);
	nbr_heredoc_bis = nbr_heredoc;
	ast = ft_parsetoken(&tokens, env, &nbr_heredoc);
	//ast_printer(ast, 0);
	ft_execute_ast(ast);
	ft_free_ast(ast);
	ft_del_hdfiles(nbr_heredoc_bis);
	//system("leaks minishell");
	return ;
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char	*prompt;

	prompt = readline("\033[1;92mminishell$\033[0m ");
	while (prompt)
	{
		if (prompt && *prompt)
		{
			add_history(prompt);
			ft_pars_and_exec(prompt, env);
		}
		free(prompt);
		prompt = readline("\033[1;92mminishell$\033[0m ");
	}
	return (0);
}
