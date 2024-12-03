/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:55:32 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/03 09:55:38 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	to remove an environment variable 
		unset <VAR_NAME>
*/

void	free_envv(t_env *current)
{
	if (current)
	{
		free(current->name);
		free(current->value);
		free(current);
	}
}
void ft_delvar(char *varname, t_env **env)
{
	t_env *current;
	t_env *prev;
	int	i;

	i = 0;
	current = *env;
	prev = NULL;
	while (current)
	{
		if (!strcmp(current->name, varname))
		{
			if (prev == NULL)
				*env = current->next;
			else
				prev->next = current->next;
			free_envv(current);
			return;
		}
		prev = current;
		current = current->next;	
	}
}

void	unset(char **argv, t_env **env)
{
	int		i;

	i = 0;
	while(argv[i])
		ft_delvar(argv[i++], env);
}
