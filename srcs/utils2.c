/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:18:18 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/19 15:34:46 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_len_int(int nbr)
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
	int		len;
	char	*string;

	n = nbr;
	if (nbr == 0)
		return (ft_strdup("0"));
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
		string[--len] = '0' + (n % 10);
		n /= 10;
	}
	return (string);
}

char	*ft_strndup(const char *s1, int len)
{
	char	*result;
	int		i;

	if (!s1)
		return (NULL);
	if (len > (int)ft_strlen(s1))
		len = ft_strlen(s1);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
