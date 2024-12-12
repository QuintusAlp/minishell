/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_tokens2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:49:27 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/12 16:54:00 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    set_flags(char c, t_trim *trim, char *result)
{
    if (c == '\'' && trim->in_double == 0)
    {
        if (!(trim->in_double))
            trim->in_single = 1;
        else 
            trim->in_single = 0;
    }
    else if (c == '\"' && trim->in_single == 0)
    {
        if (!(trim->in_double))
            trim->in_double = 1;
        else
            trim->in_double = 0;
    }
    else
    {
        result[trim->j] = c;
        (trim->j)++;
    }
    if (c == '\'')
        trim->c += 1;
}

char *trim_quotes(char *str, t_trim *trim)
{
    char    *result;

    trim->i = 0;
    trim->j = 0;
    result = malloc((ft_strlen(str) + 1) * sizeof(char));
    if (!result)
        return (NULL);
    while (str[trim->i])
    {
        set_flags(str[trim->i], trim, result);
        trim->i++;
    }
    result[trim->j] = '\0';
    return (result);
}

char *replace_env_vars(char *str, t_env **g_env, t_trim *trim) 
{
    char    *new_str;
    char    *env_value;
    char    *var_name;

    trim->i = 0;
    if (!str[trim->i] || !str[trim->i + 1] || !(ft_isalnum(str[trim->i + 1])))
        return (NULL);
    trim->i++;
    while (str[trim->i] && (isalnum(str[trim->i]) || str[trim->i] == '_' || str[trim->i] == '$')) 
        trim->i++;
    var_name = ft_strndup(&str[1], trim->i - 1);
    env_value = ft_getenv(var_name, g_env);
    free(var_name);
    if (!env_value)
        new_str = ft_strdup("");
    else 
        new_str = ft_strdup(env_value);
    trim->end_index = trim->i;
    return (new_str);
}

void interrogation(char *new_str, t_trim *trim)
{
    char    *exitcode_str;
    
    exitcode_str = ft_itoa(g_exitcode);
    strncpy(&new_str[trim->j], exitcode_str, ft_strlen(exitcode_str));
    trim->j += ft_strlen(exitcode_str);
    free(exitcode_str);
    (trim->i)++;
}

void    init_trim(t_trim *trim)
{
    trim->in_double = 0;
    trim->in_single = 0;
    trim->c = 0;
    trim->end_index = 0;
    trim->j = 0;
    trim->i = 0;
    trim->flag = 0;
}
