/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:53:14 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/05 16:53:16 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error(const char *error)
{
	ft_putstr_fd("Error :", 2);
	ft_putstr_fd(error, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

void	free_str(char *str)
{
	if (!str)
		return;
	free(str);
	str = NULL;
}

void	free_env(void)
{
	t_env	*tmp;

	tmp = NULL;
	while (g_env)
	{
		tmp = g_env;
		g_env = g_env->next;
		free(tmp->name);
		free(tmp->value);
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
