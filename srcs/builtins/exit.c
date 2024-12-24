/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:35:53 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/24 08:41:29 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    --> without arg: exit
		terminates the current shell/script
	--> with one SINGLE numeric arg: exit 42
		exits with code 42
		the value muste be [0 ; 255],
			if nbr > 255 -> changed to % 256 to be in the range
			if nbr < 0 --> changed to 256 - nbr
	--> MULTIPLE ARGS / NON-NUMERIC : error
*/

static int	str_isdigit(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			result = 0;
		i++;
	}
	return (result);
}

int	checkargvexit(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] != '0')
		return (1);
	while (is_space(str[i]))
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

void	display_error(char *str)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_exitcode = 1;
}

void	exit_code(char *argv)
{
	int		i;
	int		count;
	uint8_t	nbr;
	char	*trimmed;

	i = 0;
	count = 0;
	trimmed = ft_strdup(argv);
	while (is_space(*trimmed))
		trimmed++;
	if (trimmed[i] == '-' || trimmed[i] == '+')
		i++;
	while (ft_isdigit(trimmed[i]))
		i++;
	while (trimmed[i])
	{
		if (!is_space(trimmed[i]))
			return (display_error(trimmed));
		i++;
	}
	nbr = ft_atoi(argv);
	exit (nbr);
}

void	ft_exit(char **argv, t_env **env)
{
	(void)env;
	if (argv[1] && argv[2] && str_isdigit(argv[1])
		&& str_isdigit(argv[2]))
	{
		error("exit: too many arguments");
		g_exitcode = 1;
		return ;
	}
	ft_del_hdfiles();
	g_exitcode = 0;
	if (argv[1])
		exit_code(argv[1]);
	else
		exit(0);
}
