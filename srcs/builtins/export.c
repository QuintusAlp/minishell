/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:51:17 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/30 17:31:11 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	1. to create/change an environment variable
		export MY_VAR="voici la nouvelle valeur"
	2. to display all exported variables 
		export

	if "export new=new new2" --> only new=new appears
	if "export new=new new2=new2" --> both appears
*/

int	valid_name(char *name)
{
	int i;

	i = 0;
	if (name == NULL || ft_isdigit(name[0]))
		return (0);
	while (name)
	{
		if (!(ft_isdigit(name[i]))
			&& !(ft_isalpha(name[i]))
			&& name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// CHECK FOR SPECIAL CHARS ESCAPE
int valid_value(char *value)
{
	int i;
	
	i = 0;
	if (value == NULL)
		return (0);
	while (value[i])
	{
		if (!(ft_isalpha(value[i])))
			return (0);
	}
	return (1);
}

// static void	set_envv(const char *name, const char *value, t_env **env)
// {
// 	t_env	*current;
// 	t_env	*new;

// 	current = *env;
// 	while (current)
// 	{
// 		if (ft_strcmp(name, current->name) == 0)
// 		{
// 			free(current->value);
// 			current->value = ft_strdup(value);
// 			return;
// 		}
// 		current = current->next;
// 	}
// 	new = (t_env *)malloc(sizeof(t_env));
// 	if (!new)
// 		error("New envv malloc error");
// 	new->name = ft_strdup(name);
// 	new->value = ft_strdup(value);
// 	new->next = NULL;
// 	if (*env == NULL)
// 	{
// 		new->index = 0;
// 		*env = new;
// 	}
// 	else
// 	{
// 	new->index = current->index + 1;
// 	current->next = new;	
// 	}
// }
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
			write(1, "\n", 1);
		}
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
		if (!ft_isalnum(var[j]) && !(var[j] == '_') && !(var[j] == '='))
			return (ft_varerror(var), 1);
		j++;
	}
	return (0);
}
//add var to env
t_env *ft_newvar(char *name, char *value, int index)
{
	t_env *newvar;

	newvar = malloc(sizeof(t_env));
	if (!newvar)
		return (NULL);
	newvar->value = value;
	newvar->name = name;
	newvar->index = index;
	newvar->next = NULL;
	return (newvar);
}
//insert var into the env
int	ft_findvar(t_env *var, t_env *env)
{
	(void)var;
	while (env)
	{
		env = env->next;

	}
	return (0);
}

void ft_insertvar(t_env *var, t_env *env)
{
	printf("var->name: %s\n var->value: %s\n", var->name, var->value);
	if (ft_findvar(var, env))
		return ;  
	// while (env)
	// {
	// 	printf("name: %s\n", env->name);
	// 	env = env->next;

	// }
}
void ft_addvar(char *var, t_env *env)
{
	char **data;

	data = ft_split(var, '=');
	ft_insertvar(ft_newvar(data[0], data[1], 0), env);
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
			ft_addvar(argv[i], *env);
		else
			return (1);
		i++;
	}
	return 0;
}