/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:51:17 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/04 17:03:18 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	1. to create/change an environment variable
		export MY_VAR="voici la nouvelle valeur"
	2. to display all exported variables 
		export
*/

int	valid_name(char *name)
{
	int i;

	i = 0;
	if (name == NULL || is_digit(name[0]))
		return (0);
	while (name)
	{
		if (!(is_digit(name[i]))
			&& !(is_alpha(name[i]))
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
		if (!(is_alpha(value[i])))
			return (0);
	}
}

static void	set_envv(const char *name, const char *value)
{
	t_env	*current;
	t_env	*new;

	current = g_env;
	while (current)
	{
		if (ft_strcmp(name, current->name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return;
		}
		current = current->next;
	}
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		error("New envv malloc error");
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (g_env == NULL)
	{
		new->index = 0;
		g_env = new;
	}
	else
	{
	new->index = current->index + 1;
	current->next = new;	
	}
}

void	export(char **argvs)
{
	char **result;
	char **input;

	// input = remove_first(argvs);
	input = &argvs[1];
	
	if (input == NULL || (*input) == NULL)
		return;
	
	// split avant et apres le =
	result = ft_split(input, '=');
	
	// verifier si le name & value sont valid 
	if (valid_name(result[0]) == 0)
		error("Incorrect variable name\n");
	if (valid_value(result[1]) == 0 || result[2])
		error("Incorrect environmental variable value\n");
	set_envv(result[0], result[1]);
}