/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:18:18 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/05 16:12:42 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int ft_len_int(int nbr)
{
	int	len;

	len = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		len++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	long	n;
	int	len;
	char	*string;

	n = nbr;
	len = ft_len_int(nbr);
	string = malloc((len + 1) * sizeof(char));
	if (string == NULL)
		return (0);
	string[len] = '\0';
	if (n == 0)
		string[0] = '0';
	if (n < 0)
	{
		string[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		len--;
		string[len] = '0' + (n % 10);
		n /= 10;	
	}
	return (string);
}
