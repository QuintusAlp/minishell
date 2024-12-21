/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   trim_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:59:12 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/19 17:47:21 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//process double

int	ft_str(char *str, t_trim *trim)
{
	int		len;
	int		i;
	char	*buff;

	len = 0;
	while (str[len] && str[len] != '\"' && str[len] != '$')
		len++;
	buff = malloc(len + 1);
	i = 0;
	while (i < len)
	{
		buff[i] = str[i];
		i++;
	}
	buff[i] = '\0';
	add_to_newstr(buff, trim);
	return (len);
}

void	process_doubles(char *str, t_trim *trim, t_env **g_env)
{
	char	*tmp;

	trim->k = 1;
	while (str[trim->k] && str[trim->k] != '\"')
		trim->k++;
	tmp = ft_strndup(&str[1], (trim->k - 1));
	if (ft_strchr(tmp, '$') != NULL)
	{
		trim->k = 0;
		while (trim->k < (int)ft_strlen(tmp))
		{
			if (tmp[trim->k] == '$')
				trim->k += process_dollar(&tmp[trim->k], trim, g_env);
			else
				trim->k += ft_str(&tmp[trim->k], trim);
		}
		trim->i += trim->k;
		trim->i += 2;
		return ;
	}
	process_simple_str(tmp, trim);
	trim->i += 2;
	free(tmp);
}

char	*process_token(char *str, t_env **g_env, t_trim *trim)
{
	if (!ft_strchr(str, '$') && !ft_strchr(str, '\'')
		&& !ft_strchr(str, '\"'))
		return (str);
	while (str[trim->i])
	{
		if (str[trim->i] == '\"')
			process_doubles(&str[trim->i], trim, g_env);
		else if (str[trim->i] == '\'')
			process_singles(&str[trim->i], trim);
		else if (str[trim->i] == '$')
		{
			trim->i += process_dollar(&str[trim->i], trim, g_env);
		}
		else
			process_simple_str(&str[trim->i], trim);
	}
	return (trim->new_str);
}

void	trim_tokensv2(t_list *tokens, t_env **g_env)
{
	t_trim	trim;
	char	*str;
	t_list	*current;

	current = tokens;
	while (current)
	{
		init_trim(&trim);
		str = ft_strdup((char *)current->value);
		free(current->value);
		current->value = NULL;
		if (ft_strncmp(str, "~", ft_strlen(str)) == 0)
			current->value = ft_strdup(get_env_value("HOME", g_env));
		else
			current->value = process_token(str, g_env, &trim);
		current = current->next;
	}
}
