/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:40:11 by qalpesse          #+#    #+#             */
/*   Updated: 2024/11/14 17:32:18 by qalpesse         ###   ########.fr       */
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
	extern char	**environ;


	builtins(cmd);
	//exit(12);
	//COMBERTISSEUR CHAIN LIST -> DOUBLE TAB pour env
	
	if (execve(ft_path(cmd->argv[0], environ), cmd->argv, environ) == -1) // g_env was previsously cmd->env
		ft_panic("cmd not found", cmd->argv[0], 127);
	dprintf(2, "cmd\n");
}
