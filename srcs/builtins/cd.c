/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:14:49 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/24 10:49:25 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	only_cd(t_env **env)
{
	t_env	*home_var;

	home_var = find_key("HOME", env);
	if (home_var && home_var->value)
	{
		if (chdir(home_var->value) != 0)
			return (perror("cd"), 1);
		update_envv("OLDPWD", find_key("PWD", env)->value, env);
		update_envv("PWD", home_var->value, env);
	}
	else
		return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	return (0);
}

static int	minus_cd(t_env **env)
{
	t_env	*oldpwd_var;
	t_env	*pwd_var;

	oldpwd_var = find_key("OLDPWD", env);
	pwd_var = find_key("PWD", env);
	if (!oldpwd_var || !oldpwd_var->value || oldpwd_var->value[0] == '\0')
		return (ft_putstr_fd("bash: cd: OLDPWD not set\n", 2), 1);
	if (chdir((const char *)oldpwd_var) != 0)
	{
		ft_putstr_fd(pwd_var->value, 1);
		ft_putchar_fd('\n', 1);
	}
	else
	{
		if (pwd_var && pwd_var->value)
			update_envv("OLDPWD", find_key("PWD", env)->value, env);
		update_envv("PWD", oldpwd_var->value, env);
		ft_putstr_fd(oldpwd_var->value, 1);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}

static int	basic_cd(char *path, t_env **env)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putstr_fd("bash: cd: no such file or directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
		g_exitcode = 1;
		return (1);
	}
	if (chdir(path) != 0)
		return (perror("cd"), 1);
	update_envv("OLDPWD", cwd, env);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_envv("PWD", cwd, env);
	else
		return (perror("getcwd"), 1);
	return (0);
}

static int	tilde_cd(char *path, t_env **env)
{
	char	*new;

	new = malloc((7 + ft_strlen(&path[1])) * sizeof(char));
	if (!new)
		return (1);
	if (strcmp(path, "~") == 0 || strcmp(path, "~/") == 0)
		return (only_cd(env));
	else if (strncmp(path, "~/", 2) == 0 && ft_strlen(path) > 2)
	{
		only_cd(env);
		return (basic_cd(&path[2], env));
	}
	else if (strncmp(path, "~", 1) == 0 && ft_strlen(path) > 1)
	{
		ft_strlcpy(new, "/Users/", 7);
		ft_strlcat(new, &path[1], (ft_strlen(new)));
		if (access(new, F_OK) == -1 || access(new, X_OK) == -1)
			return (perror("cd"), 1);
		else
			return (basic_cd(new, env));
	}
	return (0);
}

void	cd(char **argv, t_env **env)
{
	char	**input;

	input = &argv[1];
	if (!find_key("PWD", env))
		return ;
	if (list_size(input) > 1 || list_size(input) < 0)
		error("cd: too may arguments");
	if (list_size(input) == 0 || ft_strncmp(input[0], "--", INT_MAX) == 0)
		only_cd(env);
	else if (ft_strncmp(input[0], "-", INT_MAX) == 0)
		minus_cd(env);
	else if (ft_strncmp(input[0], "~", INT_MAX) == 0)
		tilde_cd(input[0], env);
	else
		basic_cd(input[0], env);
}
