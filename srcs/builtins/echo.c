/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:14:27 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/24 08:00:32 by qalpesse         ###   ########.fr       */
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

bool	only_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (false);
	}
	return (true);
}

bool	option_new_line(char **args, int *p)
{
	bool	result;

	result = false;
	while (args[*p] && args[*p][0] == '-')
	{
		if (args[*p][0] == '-' && only_n(args[*p]))
		{
			(*p) += 1;
			result = true;
		}
		else
			break ;
	}
	return (result);
}

int	echo(char **argv)
{
	bool	new_line;
	int		i;
	char	**args;

	if (!(argv[1]))
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 1;
	new_line = option_new_line(argv, &i);
	args = argv;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line == false)
		write(1, "\n", 1);
	return (g_exitcode = 0, 0);
}
