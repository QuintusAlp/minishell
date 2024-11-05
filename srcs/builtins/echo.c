/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:14:27 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/05 15:05:37 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Handling the -n option:
		-> if command == "echo -n <string>"
		then no \n after the string 
*/

// function to check for "-n..."
static int check_flag(char **str)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 1;
	flag = 0;
	while (is_space(str[i]) && str[i])
	{
		if (str[i + 1] == '-')
		{
			while (str[i + 1 + j] == 'n')
			{
				if (!(is_space(str[i + 1 + j + 1])))
					return (i);
				j++;
				flag++;
			}
		}
		else 
			return (flag);
		i++;
	}
	return (flag);
}

int echo(char **argv)
{
	int	flag;
	int	i;
	char	**str;
	
	i = check_flag(str);
	str = &argv[1];
	while (str[i])
	{
		write(1, str[i], ft_strlen(str[i]));// WHERE TO WRITE --> STDOUT_FILENO ???
		if (str[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (i == 0)
		write(1, "\n", 1);
	return (0);
}