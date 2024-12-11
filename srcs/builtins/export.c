/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:51:17 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/11 15:15:19 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	1. to create/change an environment variable
		export MY_VAR="voici la nouvelle valeur"
	2. to display all exported variables
		export

	if "export new=new new2=new2" --> both appears
*/

t_env	*ft_newvar(char *name, char *value)
{
	t_env	*newvar;

	newvar = malloc(sizeof(t_env));
	if (!newvar)
		return (NULL);
	newvar->value = ft_strdup(value);
	newvar->name = ft_strdup(name);
	newvar->next = NULL;
	return (newvar);
}

static char	*data1_maker(char **data)
{
	int		i;
	char	*new_value;
	char	*temp;

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
	return (data[1]);
}

void	ft_addvar(char *var, t_env **env)
{
	char	**data;
	t_env	*env_var;

	data = ft_split(var, '=');
	if (data[1] && data[2])
		data[1] = data1_maker(data);
	if (ft_strchr((const char *)var, '=') && !data[1])
	{
		data[1] = malloc(1);
		if (!(data[1]))
			return ;
		data[1][1] = '\0';
	}
	env_var = ft_newvar(data[0], data[1]);
	ft_findplace(*env, env_var);
}

int	export(char **argv, t_env **env)
{
	int	i;
	int	plus_egal;

	i = 1;
	plus_egal = 0;
	if (!argv[i])
		return (ft_print_exportenv(*env));
	while (argv[i])
	{
		if (!ft_checkarg(argv[i], &plus_egal))
		{
			if (plus_egal == 1)
				ft_addvar_plusegal(argv[i], env);
			else
				ft_addvar(argv[i], env);
		}
		else
		{
			g_exitcode = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
