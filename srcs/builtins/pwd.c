/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:50:24 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/11 15:15:32 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	using getcwd(char *buf, size_t size)
*/

int	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		error(strerror(errno));
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free_str(pwd);
	return (0);
}
