/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:22:35 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/04 11:39:30 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	env displays a list of all environmental variables of the sessions and their current values 
		-> getenv(const char *name) with name = a given environmental variable 
			--> to retrieve the value of a variable with its name , returns a char *
*/

t_env *	remaining_env(void)
{
	t_env	*pwd_struct;
	t_env	*shlvl_struct;
	t_env	*_struct;
	char	*pwd;
	char	*_value;
	
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return NULL;
	pwd_struct = ft_newvar(ft_strdup("PWD"), ft_strdup(pwd));
	_value = ft_strjoin(pwd, "/minishell");
	free(pwd);
	shlvl_struct = ft_newvar(ft_strdup("SHLVL"), ft_strdup("1"));
	pwd_struct->next = shlvl_struct;
	_struct = ft_newvar(ft_strdup("_"), ft_strdup(_value));
	free(_value);
	shlvl_struct->next = _struct;
	_struct->next = NULL;
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

void	env(t_env **env)
{
	t_env *var;

	var =  *env;
	while(var)
	{
		if (var->value)
		{
			ft_printf("%s", var->name);
			write(1, "=", 1);
			ft_printf("%s", var->value);
			write(1, "\n", 1);
		}
		var = var->next;
	}
}
