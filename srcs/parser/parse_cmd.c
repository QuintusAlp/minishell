/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:25:55 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/17 14:55:07 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*ft_cmdnode(char **argv, char **env, t_list **token)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->type = CMD;
	cmd->argv = argv;
	cmd->env = env;
	ft_lstclear(token, &free);
	return ((t_node *)cmd);
}

char **ft_getargv(t_list *token)
{
	char **argv;
	int	i;

	argv = malloc((ft_lstsize(token) + 1) * sizeof(char *));
	i = 0;
	while (token)
	{
		argv[i] = ft_strdup(token->value);
		i++;
		token = token->next;
	}
	argv[i] = NULL;
	return (argv);
}
