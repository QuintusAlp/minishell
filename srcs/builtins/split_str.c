/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:02:22 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/05 11:47:22 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_charset_check(char c, char *charset)
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

static int	ft_split_count(char *str, char *charset)
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

static int	ft_wordlen(char *str, char *charset)
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
	array = (char **) malloc((ft_split_count(str, charset) + 1) 
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

// int main()
// {
//     //printf("count: %d\n", ft_count("coucou+=cest+=moi", "+="));
//     char **data = ft_split_str("coucou+=cest+=moi", "+=");
//     int i = 0;
//     while (data[i])
//     {
//         printf("string nbr %d: %s\n", i, data[i]);
//         if (!data[1])
//             printf("que un string mskn\n");
//         i++;
//     }
// }
