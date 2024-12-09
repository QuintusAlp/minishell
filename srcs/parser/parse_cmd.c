/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:25:55 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/09 12:32:51 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*ft_cmdnode(char **argv, t_env **g_env, t_list **token)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->type = CMD;
	cmd->argv = argv;
	cmd->g_env = g_env;
	ft_lstclear(token, &free);
	return ((t_node *)cmd);
}

char	**ft_getargv(t_list *token)
{
	char	**argv;
	int		i;

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
