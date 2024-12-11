/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:02:22 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/11 15:15:51 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_charset_check(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_split_count(char *str, char *charset)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && ft_charset_check(str[i], charset))
			i++;
		if (str[i] != '\0' && !(ft_charset_check(str[i], charset)))
			c++;
		while (str[i] != '\0' && !(ft_charset_check(str[i], charset)))
			i++;
	}
	return (c);
}

int	ft_wordlen(char *str, char *charset)
{
	int	l;

	l = 0;
	while (str[l] && !(ft_charset_check(str[l], charset)))
		l++;
	return (l);
}

char	*ft_word(char *str, char *charset)
{
	int		i;
	int		len;
	char	*word;

	i = 0;
	len = ft_wordlen(str, charset);
	word = malloc((len + 1) * sizeof(char));
	if (word == NULL)
		return (0);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_str(char *str, char *charset)
{
	int		i;
	int		j;
	char	**array;

	i = 0;
	j = 0;
	array = (char **)malloc((ft_split_count(str, charset) + 1)
			* sizeof(char *));
	if (array == NULL)
		return (0);
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && ft_charset_check(str[i], charset))
			i++;
		if (str[i] != '\0' && !(ft_charset_check(str[i], charset)))
		{
			array[j] = ft_word(&str[i], charset);
			j++;
		}
		while (str[i] != '\0' && !(ft_charset_check(str[i], charset)))
			i++;
	}
	array[j] = 0;
	return (array);
}
