/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_plusegal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:51:32 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/05 12:05:28 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// si var existe deja alors ajouter le string a la value actuelle 
t_env *ft_newvar_plusegal(char *name, char *value, t_env **env)
{
	t_env   *newvar;
    char    *new_value;
    t_env   *env_value;
    char    *temp;

    env_value = ft_getenv(name, env);
    if (env_value == NULL)
        return(ft_newvar(name, value));
    else // add new value to current value 
    {
        new_value = malloc((ft_strlen(value) + ft_strlen(env_value) + 1) * sizeof(char));
        if (!new_value)
            return (NULL);
        new_value = ft_strdup(env_value);
        temp = new_value;
        new_value = ft_strjoin(temp, value);
        //HOW TO REFER TO THE CORRECT ENV VALUE ??
    }
}

char	*ft_getenv(char *name, t_env **g_env)
{
	t_env	*current;

	current = *g_env;
	while (current)
	{
		if (ft_strcmp(name, current->name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
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
			new_value = ft_strdup(data[1]);
			while (data[i])
			{
				temp = new_value;
				new_value = ft_strjoin(new_value, "=");
				free(temp);
				temp = new_value;
				new_value = ft_strjoin(new_value, data[i]);
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
	env_var = ft_newvar_plusegal(data[0], data[1]);
	if (ft_strcmp((*env)->name, env_var->name) > 0 || *env == NULL)
		return ft_lstadd_front_env(env, env_var);
	ft_findplace(env_var, *env);
}