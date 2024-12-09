/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_plusegal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:51:32 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/09 15:50:12 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*env_match(char *name, t_env **g_env)
{
	t_env	*current;

	current = *g_env;
	while (current)
	{
		if (ft_strcmp(name, current->name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
t_env *ft_newvar_plusegal(char *name, char *value, t_env **env)
{
    char    *new_value;
    t_env   *match;

    match = env_match(name, env);
    if (match == NULL)
        return(ft_newvar_export(name, value, env));
    else
    {
        new_value = ft_strjoin(match->value, value);
        free(match->value);
        match->value = ft_strdup(new_value);
        return (match);
    }
}

static char	*split_plusegal(char **data)
{
	int		i;
	char	*new_value;
	char	*temp;
	
	i = 2;
	if (data[1])
		new_value = ft_strdup(data[1]);
	while (data[i])
	{
		temp = new_value;
		new_value = ft_strjoin(new_value, "+=");
		temp = new_value;
		new_value = ft_strjoin(temp, data[i]);
		free(temp);
		i++;
	}
	free(data[1]);
	data[1] = new_value;
	return (data[1]);
}

void ft_addvar_plusegal(char *var, t_env **env)
{
	char		**data;
	t_env		*env_var;

	data = ft_split_str(var, "+=");
	if (data[1] && data[2])
		data[1] = split_plusegal(data);
	if (ft_strnstr((const char *)var, "+=", ft_strlen(var)) && !data[1]) // adapt it for +=
			data[1] = ft_strdup("");
	env_var = ft_newvar_plusegal(data[0], data[1], env);
    if (!env_var)
        return ;
	ft_findplace(*env, env_var);
}
