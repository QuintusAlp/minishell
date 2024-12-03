/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:53:14 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/03 10:12:42 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error(const char *error)
{
	ft_putstr_fd("Error :", 2);
	ft_putstr_fd((char *)error, 2);
	ft_putchar_fd('\n', 2);
	return ;
}

void	free_str(char *str)
{
	if (!str)
		return;
	free(str);
	str = NULL;
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = NULL;
	while (env)
	{
		//printf("%s\n", env->name);
		tmp = env;
		free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		env = env->next;
		free(tmp);
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
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