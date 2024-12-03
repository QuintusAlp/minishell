/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:22:35 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/03 18:15:15 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	env displays a list of all environmental variables of the sessions and their current values 
		-> getenv(const char *name) with name = a given environmental variable 
			--> to retrieve the value of a variable with its name , returns a char *
*/

// int	export_envi(char *argv, t_env **env)
// {
// 	if (!argv)
// 		return (ft_print_exportenv(*env));
// 	if (!ft_checkarg(argv))
// 		ft_addvar(argv, env);
// 	else
// 	{
// 		g_exitcode = 1;
// 		return (1);
// 	}
// 	return (0);
// }

// t_env	*remaining_env(t_env **env)
// {
// 	char	*pwd;
// 	char	*export_;
// 	//char *str = "test=test";
	
// 	*env = (t_env *)malloc(sizeof(t_env));
// 	if (!(*env))
// 		return (error("Malloc error\n"), NULL);
// 	(*env)->name = NULL;
// 	(*env)->value = NULL;
// 	(*env)->next = NULL;
// 	pwd = getcwd(NULL, 0);
// 	if (!pwd)
// 		return (NULL);
// 	export_ = ft_strjoin("_=", pwd);
// 	export_ = ft_strjoin(export_, "/minishell");
// 	//printf("EXPORT_ : %s\n", export_);
// 	export_envi(pwd, env);
// 	export_envi("SHLVL=1", env);
// 	export_envi(export_, env);
// 	// if (export_envi(str, env) != 0)
// 	// 	return (printf("envi failed\n"), NULL);
// 	printf("laaaaaa\n");
// 	return (*env);
// }

t_env *	remaining_env(void)
{
	t_env	*pwd_struct;
	t_env	*shlvl_struct;
	t_env	*_struct;
	char	*pwd;
	
	printf("LAAAAA\n");
	//(void)env;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return NULL;
	pwd_struct = ft_newvar("PWD", pwd);
	shlvl_struct = ft_newvar(ft_strdup("SHLVL"), "1");
	pwd_struct->next = shlvl_struct;
	_struct = ft_newvar("_", ft_strjoin(pwd, "/minishell"));
	shlvl_struct->next = _struct;
	// while (*env)
	// {
	// 	printf("COUCOUU\n");
	// 	printf("%s, %s\n",(*env)->value, (*env)->name);
	// 	(*env) = (*env)->next;
	// }

	
	// _struct->name = "_";
	// _struct->value = ft_strjoin(pwd, "/minishell");
	// _struct->next = NULL;
	// shlvl_struct->name = "SHLVL";
	// shlvl_struct->value = "1";
	// shlvl_struct->next = _struct;
	// pwd_struct->name = "PWD";
	// pwd_struct->value = getcwd(NULL, 0);
	// pwd_struct->next = shlvl_struct;
	return (pwd_struct);
}

t_env *init_envv()
{
	t_env	*env;
	t_env	*current;
	t_env	*new_node;
	extern char	**environ;
	int			i;
	char		**result;

	i = 0;
	env = NULL;
	current = NULL;
	if (environ == NULL || (*environ) == NULL)
		return(remaining_env());
	while (environ[i] != NULL)
	{
		new_node = (t_env *)malloc(sizeof(t_env));
		if (!new_node)
			return(error("Malloc error\n"), NULL);
		result = ft_split(environ[i], '=');
		if (!result)
			return(free(new_node), NULL);
		new_node->name = result[0]; 
		new_node->value = result[1];
		new_node->next = NULL;
		if (!env)
			env = new_node;
		else 
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (env);
}

//CHECK THE WORKING OF ENVV
void	env(t_env **env)
{
	t_env *var;

	var =  *env;
	while(var)
	{
		if (var->value)
			ft_printf("%s=%s\n", var->name, var->value);
		var = var->next;
	}
}
