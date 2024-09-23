/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:58:39 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/18 10:46:54 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	char	*prompt;

	prompt = readline(">");
	while (prompt)
	{
		ft_parsing(prompt);
		free(prompt);
		prompt = readline("> ");
	}
	return (0);
}
