/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:37:42 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/19 17:39:10 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//-- convertissor  chain list to matrice --
int	ft_genv_size(t_env *var)
{
	int	size;

	size = 0;
	while (var)
	{
		size++;
		var = var->next;
	}
	return (size);
}

char	**ft_lst_to_matrice(t_env **g_env)
{
	char		**c_env;
	t_env		*node;
	int			i;

	c_env = NULL;
	node = *g_env;
	c_env = malloc(ft_genv_size(node) * sizeof(char *) + 1);
	i = 0;
	while (node)
	{
		c_env[i] = ft_strjoin(ft_strjoin(node->name, "="), node->value);
		i++;
		node = node->next;
	}
	c_env[i] = NULL;
	return (c_env);
}

void	ft_free_matrice(char **matrice)
{
	int	i;

	i = 0;
	while (matrice[i])
	{
		free(matrice[i]);
		i++;
	}
}

void	ft_free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}
