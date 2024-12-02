/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:14:27 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/02 15:30:41 by qalpesse         ###   ########.fr       */
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

int	ft_check_newline(char *arg, int *newline)
{
	int	j;

	if (ft_strncmp(arg, "-n", 2))
		return (1);
	*newline = 0;
	j = 2;
	while(arg[j])
	{
		if(arg[j] != 'n')
		{
			*newline = 1;
			return (1);
		}
		j++;
	}
	return (0);
}

int echo(char **argv)
{
	int	i;
	int newline;

	i = 1;
	newline = 1;
	if (!argv[i] || argv[i][0] == '\0')
		return (write(1, "\n", 1), 0);
	if (!ft_check_newline(argv[i], &newline))
		i++;
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0); // CORRECT RETURN ?
}
