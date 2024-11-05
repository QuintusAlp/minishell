/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:50:24 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/05 20:28:38 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	using getcwd(char *buf, size_t size)
*/

int pwd(void)
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