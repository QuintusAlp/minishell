/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:53:14 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/11 12:14:16 by marlonco         ###   ########.fr       */
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
		tmp = env;
		env = env->next;
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
