/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:51:17 by marlonco          #+#    #+#             */
/*   Updated: 2024/10/07 16:30:11 by marlonco         ###   ########.fr       */
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

void	export(char *input)
{
	char **result;
	
	if (input == NULL || (*input) == NULL)
		return;
	
	// split avant et apres le =
	result = ft_split(input, '='); // METTRE UN CONDITION QUE L'INDEX !> 1
	

	// verifier si le name & value sont valid 
	if (valid_name(result[0]) == 0)
		error("Incorrect variable name\n");
	if (valid_value(result[1]) == 0 || result[2])
		error("Incorrect environmental variable value\n");
	// check if la variable existe deja 

	// if existe deja 
		// update new value 

	// if pas add variable

	
}