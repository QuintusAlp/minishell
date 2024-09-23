/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:43:25 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/21 12:44:28 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_find_sep(char *s)
{
	if (ft_strrchr(s, '|'))
		return (1);
	if (ft_strrchr(s, '>'))
		return (1);
	if (ft_strrchr(s, '<'))
		return (1);
	if (ft_strrchr(s, '&'))
		return (1);
	return (0);
}
void ft_parsing(char *prompt)
{
	char **splitted_prompt;
	t_list	*tokens;
	
	splitted_prompt = ft_split(prompt, ' ');
	int i = 0;
	tokens = NULL;
	while (splitted_prompt[i])
	{
		if (!ft_find_sep(splitted_prompt[i]))
		{
			ft_lstadd_back(&tokens, ft_lstnew(splitted_prompt[i], WORD));
		//	printf("token value: %s, token type: %d\n", (char *)tokens->value, tokens->type);
		//	free(tokens);
		}
		i++;
	}
	while(tokens)
	{
		printf("token value: %s \n", (char *)tokens->value);
		printf("token type: %d \n", tokens->type);
		printf("\n");
		tokens = tokens->next;
	}
}
