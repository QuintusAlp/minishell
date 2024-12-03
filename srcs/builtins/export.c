/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:51:17 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/03 17:46:25 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	1. to create/change an environment variable
		export MY_VAR="voici la nouvelle valeur"
	2. to display all exported variables 
		export

	if "export new=new new2=new2" --> both appears
*/


//print exporte env
int ft_print_exportenv(t_env *env)
{
	while (env && env->name)
	{
		write(1, "declare -x ", 11);
		write(1, env->name, ft_strlen(env->name));
		if (env->value)
		{	
			write(1, "=", 1);
			write(1, "\"", 1);
			write(1, env->value, ft_strlen(env->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		env = env->next;
	}
	return (0);
}
//check args are valides
void	ft_varerror(char *var)
{
	write(2, "bash: export: `", 15);
	write(2, var, ft_strlen(var));
	write(2, "': not a valid identifier\n", 26);
}
int	ft_checkarg(char *var)
{
	int	j;

	if (var[0] == '=' || (var[0] >= '0' && var[0] <= '9') )
		return (ft_varerror(var), 1);
	j = 0;
	while (var[j])
	{
		if (!ft_isalnum(var[j]) && !(var[j] == '_') && !(var[j] == '=') && !(var[j] == '\'') && !(var[j] == '\"'))
			return (ft_varerror(var), 1);
		j++;
	}
	return (0);
}
//add var to env
t_env *ft_newvar(char *name, char *value)
{
	t_env *newvar;

	newvar = malloc(sizeof(t_env));
	if (!newvar)
		return (NULL);
	newvar->value = value;
	newvar->name = name;
	newvar->next = NULL;
	return (newvar);
}
//insert var into the env
void	ft_lstadd_front_env(t_env **lst, t_env *new)
{
	new->next = *lst;
	*lst = new;
}
void ft_findplace(t_env *var, t_env *env)
{
	t_env *subvar;

	while(env)
	{
		if (!ft_strcmp((env)->name, var->name))
		{
			if (var->value)
			{
				free((env)->value);
				(env)->value = ft_strdup(var->value);
				free(var->name);
				free(var->value);
				return (free(var));
			}
			else
				return ;
		}
		if (((env)->next) && ft_strcmp(((env)->next)->name, var->name) > 0)
		{
			subvar = (env)->next;
			(env)->next = var;
			var->next = subvar;
			return ;
		}
		if ((env)->next == NULL)
		{
			(env)->next = var;
			return ;
		}
		env = (env)->next;
	}
}
void ft_addvar(char *var, t_env **env)
{
	char		**data;
	t_env	*env_var;

	data = ft_split(var, '=');
	if (ft_strchr((const char *)var, '=') && !data[1])
	{
		data[1] = malloc(1);
		data[1][1] = '\0';
	}
	env_var = ft_newvar(data[0], data[1]);
	if (ft_strcmp((*env)->name, env_var->name) > 0 || *env == NULL)
		return ft_lstadd_front_env(env, env_var);
	ft_findplace(env_var, *env);
}
int	export(char **argv, t_env **env)
{
	int	i;
	
	i = 1;
	if (!argv[i])
		return (ft_print_exportenv(*env));
	while(argv[i])
	{
		if (!ft_checkarg(argv[i]))
			ft_addvar(argv[i], env);
		else
		{
			g_exitcode = 1;
			return (1);
		}
		i++;
	}
	return 0;
}