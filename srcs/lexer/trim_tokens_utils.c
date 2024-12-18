/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:32:43 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/18 16:44:57 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_env_value(char *var_name, t_env **env)
{
    t_env *var;

    var = *env;
    while(var)
    {
        if (!ft_strcmp(var_name, var->name))
        {
            return (free(var_name), ft_strdup(var->value));
        }
        else
        var = var->next;
    }
    return (free(var_name), NULL);
}

void    add_to_newstr(char *str, t_trim *trim)
{
    char *dup;

    if(!str)
        return ;
    dup = trim->new_str;
    trim->new_str = ft_strjoin(dup, str);
    if (dup)
		free(dup);
}

void    init_trim(t_trim *trim)
{
    trim->j = 0;
    trim->i = 0;
    trim->k = 0;
    trim->new_str = ft_strdup("");
    trim->temp = ft_strdup("");
}
