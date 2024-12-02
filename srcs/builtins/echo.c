/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:14:27 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/02 13:46:59 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Handling the -n option:
		-> if command == "echo -n <string>"
		--> if -nnnnnnnnnnn...n then behaves as -n
		--> if "echo -n" then new cmd line 
		then no \n after the string 
*/

int	check_flag(char *str)
{
	int	i;

	i = 1;
	while (str[i] == 'n' && str[i])
		i++;
	if (!(is_space(str[i])) && str[i])
		return (0);
	else
	{
		while (is_space(str[i]) && str[i])
			i++;
		if (str[i] && !(is_space(str[i])))
			return (0);
	}
	return(1);
}

int echo(char **argv)
{
	int		i;
	char	**str;
	int		newline;

	i = 0;
	str = &argv[1];
	newline = 1;
	if (str[0] && ft_strncmp(str[0], "-n", 2) == 0 
			&& check_flag(str[0]) == 1)
	{
		newline = 0;
		i = 1;
	}
	while (str[i])
	{
		write(1, str[i], ft_strlen(str[i]));
		if (str[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
