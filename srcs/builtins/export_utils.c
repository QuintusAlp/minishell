/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:16:28 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/20 16:42:54 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_print_exportenv(t_env *env)
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

void	update_or_insert(t_env *current, t_env *var, t_env *subvar)
{
	if (ft_strcmp((current)->name, var->name) == 0)
	{
		if (var->value)
			(current)->value = ft_strdup(var->value);
	}
	else
	{
		subvar = (current)->next;
		(current)->next = var;
		var->next = subvar;
	}
}

int	further_check(char *var, int *j, int *plus_egal)
{
	if (var[*j] == '+')
	{
		if (var[*j + 1] != '=')
			return (ft_varerror(var), 1);
		*plus_egal = 1;
		(*j) += 2;
		while (ft_isalnum(var[*j]) || var[*j] == '_' || var[*j] == '\''
			|| var[*j] == '\"' || var[*j] == '+' || var[*j] == '='
			|| var[*j] == '-')
			(*j)++;
	}
	else if (var[*j] == '=')
	{
		(*j)++;
		while (ft_isalnum(var[*j]) || var[*j] == '_' || var[*j] == '\''
			|| var[*j] == '\"' || var[*j] == '+' || var[*j] == '='
			|| var[*j] == '-')
			(*j)++;
	}
	else if (var[*j] != '\0')
		return (ft_varerror(var), 1);
	return (0);
}

int	ft_checkarg(char *var, int *plus_egal)
{
	int	j;

	if (var[0] == '=' || (var[0] >= '0' && var[0] <= '9'))
		return (ft_varerror(var), 1);
	j = 0;
	while (var[j])
	{
		while (ft_isalnum(var[j]) || var[j] == '_' || var[j] == '\''
			|| var[j] == '\"')
			j++;
		return (further_check(var, &j, plus_egal));
	}
	return (0);
}

void	ft_findplace(t_env *env, t_env *var)
{
	t_env	*subvar;
	t_env	*current;

	current = env;
	subvar = NULL;
	while (current)
	{
		if (ft_strcmp((current)->name, var->name) == 0)
		{
			update_or_insert(current, var, subvar);
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
