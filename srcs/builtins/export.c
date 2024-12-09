/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:51:17 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/09 15:58:07 by marlonco         ###   ########.fr       */
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

//TO DO: JUST EXPORT A 

int ft_print_exportenv(t_env *env)
{
	t_env	*current;

	current = env;
	while (current && current->name)
	{
		write(1, "declare -x ", 11);
		write(1, current->name, ft_strlen(current->name));
		if (current->value)
		{	
			write(1, "=", 1);
			write(1, "\"", 1);
			write(1, current->value, ft_strlen(current->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		current = current->next;
	}
	return (0);
}

void	ft_varerror(char *var)
{
	write(2, "bash: export: `", 15);
	write(2, var, ft_strlen(var));
	write(2, "': not a valid identifier\n", 26);
}

int	ft_checkarg(char *var, int *plus_egal)
{
	int	j;

	if (var[0] == '=' || (var[0] >= '0' && var[0] <= '9') )
		return (ft_varerror(var), 1);
	j = 0;
	while (var[j])
	{
		while (ft_isalnum(var[j]) || var[j] == '_' || var[j] == '\''
				|| var[j] == '\"')
			j++;
		if (var[j] == '+')
		{
			if (var[j + 1] != '=')
				return (ft_varerror(var), 1);
			*plus_egal = 1;
			j += 2;
			while (ft_isalnum(var[j]) || var[j] == '_' || var[j] == '\''
			|| var[j] == '\"' || var[j] == '+' || var[j] == '=' || var[j] == '-')
				j++;
		}
		else if (var[j] == '=')
		{
			j++;
			while (ft_isalnum(var[j]) || var[j] == '_' || var[j] == '\''
			|| var[j] == '\"' || var[j] == '+' || var[j] == '=' || var[j] == '-')
				j++;
		}
		else if (var[j] != '\0')
			return (ft_varerror(var), 1);
	}
	return (0);
}

t_env *ft_newvar(char *name, char *value)
{
	t_env *newvar;

	newvar = malloc(sizeof(t_env));
	if (!newvar)
		return (NULL);
	newvar->value = ft_strdup(value);
	newvar->name = ft_strdup(name);
	newvar->next = NULL;
	return (newvar);
}

t_env *ft_newvar_export(char *name, char *value, t_env **env)
{
	t_env *newvar;
	t_env	*current;

	newvar = malloc(sizeof(t_env));
	if (!newvar)
		return (NULL);
	newvar->value = ft_strdup(value);
	newvar->name = ft_strdup(name);
	newvar->next = NULL;
	current = *env;
	while (current->next)
		current = current->next;
	current->next = newvar;
	return (newvar);
}

void	ft_lstadd_front_env(t_env **lst, t_env *new)
{
	new->next = *lst;
	*lst = new;
}

void ft_findplace(t_env *env, t_env *var)
{
	t_env 	*subvar;
	t_env	*current;

	current = env;
	while(current)
	{
		if (ft_strcmp((current)->name, var->name) == 0)
		{
			if (var->value)
			{
				(current)->value = ft_strdup(var->value);
				return ;
			}
		}
		if (((current)->next) && ft_strcmp(((current)->next)->name, var->name) > 0)
		{
			subvar = (current)->next;
			(current)->next = var;
			var->next = subvar;
			return ;
		}
		if ((current)->next == NULL)
		{
			(current)->next = var;
			return ;
		}
		current = (current)->next;
	}
}

void ft_addvar(char *var, t_env **env)
{
	char		**data;
	t_env		*env_var;
	int			i;
	char		*temp;
	char		*new_value;

	data = ft_split(var, '=');
	if (data[2])
	{
			i = 2;
			new_value = ft_strdup(data[1]);
			while (data[i])
			{
				temp = new_value;
				new_value = ft_strjoin(new_value, "=");
				free(temp);
				temp = new_value;
				new_value = ft_strjoin(new_value, data[i]);
				free(temp);
				i++;
			}
			free(data[1]);
			data[1] = new_value;
	}
	if (ft_strchr((const char *)var, '=') && !data[1])
	{
		data[1] = malloc(1);
		if (!(data[1]))
			return;
		data[1][1] = '\0';
	}
	env_var = ft_newvar(data[0], data[1]);
	ft_findplace(*env, env_var);
}

int	export(char **argv, t_env **env)
{
	int	i;
	int	plus_egal;
	
	i = 1;
	plus_egal = 0;
	if (!argv[i])
		return (ft_print_exportenv(*env));
	while(argv[i])
	{
		if (!ft_checkarg(argv[i], &plus_egal))
		{
			if (plus_egal == 1)
				ft_addvar_plusegal(argv[i], env);
			else 
				ft_addvar(argv[i], env);
		}
		else
		{
			g_exitcode = 1;
			return (1);
		}
		i++;
	}
	return 0;
}
