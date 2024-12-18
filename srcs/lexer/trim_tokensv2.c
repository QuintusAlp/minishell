/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_tokensv2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:59:12 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/18 15:30:47 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    add_to_newstr(char *str, t_trim *trim)
{
    char *dup;

    if(!str)
        return ;
    dup = trim->new_str;
    trim->new_str = ft_strjoin(dup, str);
    free(dup);
    free(str);
}

//process dollar
char *get_env_value(char *var_name, t_env **env)
{
    t_env *var;

    var = *env;
    while(var)
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

void    process_dollar(char *str, t_trim *trim, t_env **g_env)
{
    char *var;
    int     i;
    int     len;

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

//process simples str
void process_simple_str(char *str, t_trim *trim)
{
    int len;
    int i;
    char *buff;

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
//process singles
void    process_singles(char *str, t_trim *trim)
{
    char    *tmp;
    
    trim->k = 1;
    while (str[trim->k] != '\'' && str[trim->k])
        trim->k++;
    tmp = ft_strndup(&str[1], (trim->k - 1));
    add_to_newstr(tmp, trim);
    trim->i += ft_strlen(tmp) + 2;
}

//process double
void    process_doubles(char *str, t_trim *trim, t_env **g_env)
{
    char    *tmp;
    char    *result;

    result = ft_strdup("");
    trim->k = 1;
    while (str[trim->k] && str[trim->k] != '\"')
        trim->k++;
    tmp = ft_strndup(&str[1], (trim->k - 1));
    if (ft_strchr(tmp, '$') != NULL)
    {
        trim->k = 0;
        while(trim->k < (int)ft_strlen(tmp))
        {
            if (tmp[trim->k] != '$')
                process_simple_str(&tmp[trim->k], trim);
            trim->k += 1;
            if (trim->k < (int)ft_strlen(tmp))
                process_dollar(&tmp[trim->k], trim, g_env);
        }
        trim->i += 4;
        return ;
    }
    process_simple_str(tmp, trim);
    trim->i += 2;
    free(tmp);
}

char    *process_token(char *str, t_env **g_env, t_trim *trim)
{
    if (!ft_strchr(str, '$') && !ft_strchr(str, '\'')
            && !ft_strchr(str, '\"'))
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
        printf("new_str: %s, i: %d, j: %d\n", trim->new_str, trim->i, trim->j);
    }
    return (trim->new_str);
}

void    init_trim(t_trim *trim)
{
    trim->j = 0;
    trim->i = 0;
    trim->k = 0;
    trim->new_str = ft_strdup("");
    trim->temp = ft_strdup("");
}

void    trim_tokens(t_list *tokens, t_env **g_env)
{
    t_trim     trim;
    char       *str;
    t_list     *current;
    
    init_trim(&trim);
    current = tokens;
    while (current)
    {
        str = ft_strdup((char *)current->value);
        free(current->value);
        current->value = NULL;
        current->value = process_token(str, g_env, &trim);
        current = current->next;
    }
}
