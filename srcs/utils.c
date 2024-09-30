/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:53:14 by marlonco          #+#    #+#             */
/*   Updated: 2024/09/30 10:20:35 by marlonco         ###   ########.fr       */
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