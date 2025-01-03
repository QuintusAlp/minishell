/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:15:12 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/19 16:00:13 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*coppy;
	int		i;

	if (!s1)
		return (NULL);
	coppy = malloc((ft_strlen((char *)s1) + 1) * sizeof(char));
	if (!coppy)
		return (0);
	i = 0;
	while (s1[i])
	{
		coppy[i] = s1[i];
		i++;
	}
	coppy[i] = '\0';
	return (coppy);
}

/*
#include <stdio.h>
int main(void)
{
	
	printf("%s", ft_strdup(NULL));
}*/