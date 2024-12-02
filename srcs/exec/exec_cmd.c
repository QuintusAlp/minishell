/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:40:11 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/02 13:21:03 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_binpaths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
		{
			paths = ft_split(&env[i][5], ':');
			break ;
		}
		i ++;
	}
	return (paths);
}

char	*ft_path(char *exec, char **env)
{
	char	*path;
	char	**paths;
	int		i;

	path = NULL;
	paths = ft_binpaths(env);
	if (!paths)
		ft_error("env : no comand path");
	i = 0;
	if (!access(exec, X_OK))
	{
		path = exec;
		return (path);
	}
	while (paths[i])
	{
		if (!access(ft_strjoin(paths[i], ft_strjoin("/", exec)), X_OK))
		{
			path = ft_strjoin(paths[i], ft_strjoin("/", exec));
			return (path);
		}
		i++;
	}
	return (path);
}
//-- convertissor  chain list to matrice --
int ft_genv_size(t_env *var)
{
	int size;

	size = 0;
	while (var)
	{
		size++;
		var = var->next;
	}
	return (size);
}
char **ft_lst_to_matrice(t_env **g_env)
{
	char **c_env;
	t_env *node;
	int	i;

	c_env = NULL;
	node = *g_env;
	c_env = malloc(ft_genv_size(node) * sizeof(char *) + 1);
	i = 0;
	while(node)
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
	while(matrice[i])
	{
		free(matrice[i]);
		i++;
	}
}
void	ft_exec_cmd(t_cmd *cmd)
{
	char **c_env;

	builtins(cmd);
	c_env = ft_lst_to_matrice(cmd->g_env);
	if (execve(ft_path(cmd->argv[0], c_env), cmd->argv, c_env) == -1) // g_env was previsously cmd->env
	{
		ft_free_matrice(c_env);
		ft_panic("cmd not found", cmd->argv[0], 127);
	}
}
