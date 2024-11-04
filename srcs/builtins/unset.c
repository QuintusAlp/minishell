/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:55:32 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/04 16:00:46 by marlonco         ###   ########.fr       */
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

void	unset(const char *name) // CHANGE TO THE ARG OF THE CMD
{
	t_env	*current;
	t_env	*prev;

	current = g_env;
	prev = NULL;
	if (name == NULL || *name == '\0')
		error("unset: invalid name\n");
	while (current)
	{
		if (strcmp(current->name, name) == 0)
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
}