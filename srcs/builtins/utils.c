/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:34:33 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/05 20:37:38 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_space(char c)
{
	if (!c)
		return (0);
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	list_size(char **argv)
{
	int i;

	i = 0;
	if (!argv || !(*argv))
		return (0);
	while (argv[i])
		i++;
	return (i);
}

// void	remove_first(char **argv, int *size)
// {
// 	int	i;

// 	i = 0;
// 	if (*size <= 0)
// 		return;
	
// 	free(argv[0]);
// 	while (i < *size)
// 	{
// 		argv[i-1] = argv[i];
// 		i++;
// 	}
// 	argv[*size - 1] = 0;
// 	(*size--);
// }
