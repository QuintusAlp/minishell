/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:43:22 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/11 12:44:06 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env *find_key(char *key, t_env **env)
{
    t_env *current;

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

void update_envv(char *key, char *new_value, t_env **env)
{
    t_env *var;

    var = find_key(key, env);
    if (var)
    {
        free(var->value);
        var->value = ft_strdup(new_value);
    }
}