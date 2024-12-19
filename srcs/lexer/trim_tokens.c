/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:59:12 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/18 21:13:47 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_dollar(char *str, t_trim *trim, t_env **g_env)
{
	char	*var;
	int		i;
	int		len;

	if (str[0] == '?')
	{
		var = ft_itoa(g_exitcode);
		len = 1;
	}
	else
	{
		len = 0;
		while (str[len] && str[len] != '$' && str[len] != ' '
			&& str[len] != '\'' && str[len] != '\"')
			len++;
		var = malloc(len + 1);
		i = -1;
		while (i++, i < len)
			var[i] = str[i];
		var[i] = '\0';
		var = get_env_value(var, g_env);
	}
	add_to_newstr(var, trim);
	trim->i += len;
	trim->k += len;
}

void	process_singles(char *str, t_trim *trim)
{
	char	*tmp;

	trim->k = 1;
	while (str[trim->k] != '\'')
		trim->k++;
	tmp = ft_strndup(&str[1], (trim->k - 1));
	add_to_newstr(tmp, trim);
	trim->i += ft_strlen(tmp) + 2;
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
				trim->k += ft_dolar(&tmp[trim->k], trim, g_env) + 1;
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
	if (!ft_strchr(str, '$') && !ft_strchr(str, '\'') && !ft_strchr(str, '\"'))
		return (str);
	while (str[trim->i])
	{
		if (str[trim->i] == '\"')
		{
			process_doubles(&str[trim->i], trim, g_env);
		}
		else if (str[trim->i] == '\'')
		{
			process_singles(&str[trim->i], trim);
		}
		else if (str[trim->i] == '$' && str[trim->i + 1])
		{
			trim->i += 1;
			process_dollar(&str[trim->i], trim, g_env);
		}
		else
		{
			process_simple_str(&str[trim->i], trim);
		}
	}
	return (trim->new_str);
}

void	trim_tokens(t_list *tokens, t_env **g_env)
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
			current->value = get_env_value("HOME", g_env);
		else
			current->value = process_token(str, g_env, &trim);
		current = current->next;
	}
}
