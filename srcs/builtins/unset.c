/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:55:32 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/05 20:36:03 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	to remove an environment variable 
		unset <VAR_NAME>
*/

static void	update_index(int deleted_index)
{
	t_env	*current;
	
	current = g_env;
	while (current)
	{
		if (current->index > deleted_index)
			current->index -= 1;
		current = current->next;	
	}
}

void	free_envv(t_env *current)
{
	if (current)
	{
		free(current->name);
		free(current->value);
		free(current);
	}
}

void	unset(char **argv)
{
	t_env	*current;
	t_env	*prev;
	char	**name;
	int		i;

	name = &argv[1];
	i = 0;
	if (name == NULL || **name == '\0')
		error("unset: invalid name\n");
	while (name[i])
	{
		current = g_env;
		prev = NULL;
		while (current)
		{
			if (strcmp(current->name, name[i]) == 0)
			{
				if (prev == NULL)
					g_env = current->next;
				else
					prev->next = current->next;
				update_index(current->index);
				free_envv(current);
				return;
			}
			prev = current;
			current = current->next;	
		}
		i++;
	}
}
