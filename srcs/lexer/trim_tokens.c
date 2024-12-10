/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 07:18:36 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/10 13:32:27 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_trim
{
    bool    in_single;
    bool    in_double;
    int     c;
    int     end_index;
}   t_trim;

static char	*ft_strndup(const char *s1, int len)
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
// void ft_putinresult(char *result, char *str, t_trim *trim, int *i, int *j)
// {
//     while (str[*i])
//     {
//         if (str[*i] == '\'' && trim->in_double == 0)
//         {
//             if (!(trim->in_double))
//                 trim->in_single = 1;
//             else 
//                 trim->in_single = 0;
//         }
//         else if (str[*i] == '\"' && trim->in_single == 0)
//         {
//             if (!(trim->in_double))
//                 trim->in_double = 1;
//             else
//                 trim->in_double = 0;
//         }
//         else 
//             result[*j++] = str[*i];
//         if (str[*i] == '\'')
//             trim->c += 1;
//         (*i)++;
//     }
//     result[*j] = '\0';
// }
// static char *trim_quotes(char *str, t_trim *trim)
// {
//     char    *result;
//     int     i;
//     int     j;
    
//     i = 0;
//     j = 0;
//     result = malloc((ft_strlen(str) + 1) * sizeof(char));
//     if (!result)
//         return (NULL);
//     ft_putinresult(result, str, trim, &i, &j);

//     return (result);
// }

// void    set_flags(char c, t_trim *trim, char **result, int *j)
// {
//     if (c == '\'' && trim->in_double == 0)
//     {
//         if (!(trim->in_double))
//             trim->in_single = 1;
//         else 
//             trim->in_single = 0;
//     }
//     else if (c == '\"' && trim->in_single == 0)
//     {
//         if (!(trim->in_double))
//             trim->in_double = 1;
//         else
//             trim->in_double = 0;
//     }
//     else
//     {
//         *result[*j] = c;
//         (*j)++;
//     }
//     if (c == '\'')
//         trim->c += 1;
// }

static char *trim_quotes(char *str, t_trim *trim)
{
    int i;
    int j;
    char    *result;
    
    i = 0;
    j = 0;
    result = malloc((ft_strlen(str) + 1) * sizeof(char));
    if (!result)
        return (NULL);
    while (str[i])
    {
        if (str[i] == '\'' && trim->in_double == 0)
        {
            if (!(trim->in_double))
               trim->in_single = 1;
            else 
                trim->in_single = 0;
        }
        else if (str[i] == '\"' && trim->in_single == 0)
        {
            if (!(trim->in_double))
                trim->in_double = 1;
            else
                trim->in_double = 0;
        }
        else 
            result[j++] = str[i];
        if (str[i] == '\'')
            trim->c += 1;
        // set_flags(str[i], trim, &result, &j);
        i++;
    }
    result[j] = '\0';
    return (result);
}

char *replace_env_vars(char *str, t_env **g_env, t_trim *trim) 
{
    char    *new_str;
    char    *env_value;
    char    *var_name;
    int     i;

    i = 0;
    if (!str[i] || !str[i + 1] || !(ft_isalnum(str[i + 1])))
        return (NULL);
    i++;
    while (str[i] && (isalnum(str[i]) || str[i] == '_')) 
        i++;
    var_name = ft_strndup(&str[1], i - 1);
    env_value = ft_getenv(var_name, g_env);
    free(var_name);
    if (!env_value)
        new_str = ft_strdup("");
    else 
        new_str = ft_strdup(env_value);
    trim->end_index = i;
    return (new_str);
}

void trim_tokens(t_list *tokens, t_env **g_env)
{
    char *str;
    char *new_str;
    int  i;
    int  j;
    t_trim  trim;

    i = 0;
    j = 0;
    trim.in_double = 0;
    trim.in_single = 0;
    trim.c = 0;
    trim.end_index = 0;
    while (tokens) 
    {
        str = (char *)tokens->value;
        str = trim_quotes(str, &trim);
        new_str = malloc(1024 * sizeof(char));
        if (!new_str)
            return;
        i = 0;
        j = 0;
         while (str[i])
         {
            if (str[i] == '$' && str[i + 1] && (!(trim.in_single) || trim.c == 0))
            {
                if (str[i + 1] == '?')
                {
                    char    *exitcode_str = ft_itoa(g_exitcode);
                    strncpy(&new_str[j], exitcode_str, ft_strlen(exitcode_str));
                    j += ft_strlen(exitcode_str);
                    free(exitcode_str);
                    i++;
                }
                else 
                {
                    char *expanded = replace_env_vars(&str[i], g_env, &trim);
                    strncpy(&new_str[j], expanded, ft_strlen(expanded));
                    j += ft_strlen(expanded);
                    free(expanded);
                    i += trim.end_index - 1;  
                }
            } 
            else
                new_str[j++] = str[i];
            i++;
        }
        new_str[j] = '\0';
        free(tokens->value);
        tokens->value = new_str;
        tokens = tokens->next;
    }  
}
