/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:14:27 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/30 17:47:38 by qalpesse         ###   ########.fr       */
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

// DO I NEED THE ENVV VAR ?
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
	int	i;
	int newline;

	i = 1;
	newline = 1;
	if (!argv[i] || argv[i][0] == '\0')
		return (write(1, "\n", 1), 0);
	if (!ft_strncmp(argv[i], "-n", 2))
	{
		printf("lol\n");
		i++;
		newline = 0;
		if (!check_flag(argv[1]))
			return 1;
	}
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
