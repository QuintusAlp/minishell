/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_plusegal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:51:32 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/09 11:04:05 by marlonco         ###   ########.fr       */
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
    else // add new value to current value 
    {
        new_value = ft_strjoin(match->value, value);
        free(match->value);
        match->value = ft_strdup(new_value);
        return (match);
    }
}


void ft_addvar_plusegal(char *var, t_env **env)
{
	char		**data;
	t_env		*env_var;
	int			i;
	char		*temp;
	char		*new_value;

	data = ft_split_str(var, "+=");
	if (data[2]) // condition alors ca va dans le string genre export y+=x+=z --> y = x+=z
	{
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
	}
	if (ft_strchr((const char *)var, '=') && !data[1]) // adapt it for +=
	{
			data[1] = malloc(1);
			if (!(data[1]))
				return;
			data[1][1] = '\0';
	}
	env_var = ft_newvar_plusegal(data[0], data[1], env);
	printf("ft_addvar_pluseagal, var name to be added: %s\n var value: %s\n", env_var->name, env_var->value);
    if (!env_var)
        return ;
	ft_findplace(*env, env_var);
}