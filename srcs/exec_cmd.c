/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:40:11 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/15 14:42:29 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	ft_exec_cmd(t_cmd *cmd, int *pipefd, int dupfd, int *cmd_index)
{
	(void)pipefd;
	(void)dupfd;
	(void)cmd_index;
	
	if (execve(ft_path(cmd->argv[0],cmd->env),cmd->argv, cmd->env) == -1)
		ft_error("cmd error");
}