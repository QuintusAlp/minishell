/* ************************************************************************** */
/*				                                                              */
/*                                                        :::      ::::::::   */
/*   trim_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:32:43 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/19 15:19:10 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *var_name, t_env **env)
{
	t_env	*var;

	var = *env;
	while (var)
	{
		if (!ft_strcmp(var_name, var->name))
		{
			return (free(var_name), ft_strdup(var->value));
		}
		else
			var = var->next;
	}
	return (free(var_name), NULL);
}

void	add_to_newstr(char *str, t_trim *trim)
{
	char	*dup;

	if (!str)
		return ;
	dup = trim->new_str;
	trim->new_str = ft_strjoin(dup, str);
	if (dup)
		free(dup);
}

void	init_trim(t_trim *trim)
{
	trim->j = 0;
	trim->i = 0;
	trim->k = 0;
	trim->new_str = ft_strdup("");
	trim->temp = ft_strdup("");
}

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

void	process_simple_str(char *str, t_trim *trim)
{
	int		len;
	int		i;
	char	*buff;

	len = 0;
	while (str[len] && str[len] != '\'' && str[len] != '\"' && str[len] != '$')
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
	trim->i += len;
	trim->k += len;
}
