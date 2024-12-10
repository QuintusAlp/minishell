/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:40:11 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/10 15:43:54 by qalpesse         ###   ########.fr       */
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

void	ft_exec_cmd(t_cmd *cmd)
{
	char	**c_env;

	builtins(cmd);
	c_env = ft_lst_to_matrice(cmd->g_env);
	// signal(SIGINT, SIG_DFL);
    // signal(SIGQUIT, SIG_DFL);
	if (execve(ft_path(cmd->argv[0], c_env), cmd->argv, c_env) == -1)
	{
		ft_free_matrice(c_env);
		ft_panic("cmd not found", cmd->argv[0], 127);
	}
}
