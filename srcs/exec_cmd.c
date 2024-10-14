/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:40:11 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/14 16:10:34 by qalpesse         ###   ########.fr       */
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
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_error("fork error");
	if (pid == 0)
	{
		if (*cmd_index == 0)
		{
			if (pipefd)
			{
				if (dup2(pipefd[1], 1) == -1)
					ft_error("dup2 error 1");
			}
		}
		if (*cmd_index == -1)
		{
			if (dup2(dupfd, 0) == -1)
					ft_error("dup2 error 2");
		}
		if (*cmd_index > 0)
		{
			if (dup2(dupfd, 0) == -1)
				ft_error("dup2 error 2");
			if (dup2(pipefd[1], 1) == -1)
				ft_error("dup2 error 3");
		}
		if (pipefd)
		{
			close(pipefd[1]);
			close(pipefd[0]);
		}
		if (dupfd != -1)
			close(dupfd);
		if (execve(ft_path(cmd->argv[0],cmd->env),cmd->argv, cmd->env) == -1)
			ft_error("cmd error");
	}
}
