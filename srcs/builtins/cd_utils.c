/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:48:27 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/11 14:54:15 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*find_key(char *key, t_env **env)
{
	t_env	*current;

	current = *env;
	if (!key || !current)
		return (NULL);
	while (current)
	{
		if (ft_strncmp(current->name, key, INT_MAX) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	update_envv(char *key, char *new_value, t_env **env)
{
	t_env	*var;

	var = find_key(key, env);
	if (var)
	{
		free(var->value);
		var->value = ft_strdup(new_value);
	}
}
