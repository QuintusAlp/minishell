/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 07:18:36 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/11 14:32:16 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_trim
{
    bool    in_single;
    bool    in_double;
    int     c;
    int     end_index;
    int     i;
    int     j;
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

static char *trim_quotes(char *str, t_trim *trim)
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
    while (str[trim->i] && (isalnum(str[trim->i]) || str[trim->i] == '_')) 
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

static void interrogation(char *new_str, t_trim *trim)
{
    char    *exitcode_str;
    
    exitcode_str = ft_itoa(g_exitcode);
    strncpy(&new_str[trim->j], exitcode_str, ft_strlen(exitcode_str));
    trim->j += ft_strlen(exitcode_str);
    free(exitcode_str);
    (trim->i)++;
}

// static void expanded(char *new_str, int *i, int *j, t_env **g_env)
// {
//     char    *expanded;
    
//     expanded = replace_env_vars(&str[*i], g_env, &trim);
//     strncpy(&new_str[*j], expanded, ft_strlen(expanded));
//     j += ft_strlen(expanded);
//     free(expanded);
//     i += trim.end_index - 1;  
// }

static void    init_trim(t_trim *trim)
{
    trim->in_double = 0;
    trim->in_single = 0;
    trim->c = 0;
    trim->end_index = 0;
    trim->j = 0;
    trim->i = 0;
}

// void trim_tokens(t_list *tokens, t_env **g_env)
// {
//     char *str;
//     char *new_str;
//     int  i;
//     int  j;
//     t_trim  trim;

//     i = 0;
//     j = 0;
//     init_trim(&trim);
//     while (tokens) 
//     {
//         str = (char *)tokens->value;
//         str = trim_quotes(str, &trim);
//         new_str = malloc(1024 * sizeof(char));
//         if (!new_str)
//             return;
//         i = 0;
//         j = 0;
//          while (str[i])
//          {
//             if (str[i] == '$' && str[i + 1] && (!(trim.in_single) || trim.c == 0))
//             {
//                 if (str[i + 1] == '?')
//                     interrogation(new_str, &j, &i);
//                 else 
//                 {
//                     //char *expanded = replace_env_vars(&str[i], g_env, &trim);
//                     strncpy(&new_str[j], replace_env_vars(&str[i], g_env, &trim), ft_strlen(replace_env_vars(&str[i], g_env, &trim)));
//                     j += ft_strlen(replace_env_vars(&str[i], g_env, &trim));
//                     //free(expanded);
//                     i += trim.end_index - 1;  
//                 }
//             } 
//             else
//                 new_str[j++] = str[i];
//             i++;
//         }
//         new_str[j] = '\0';
//         free(tokens->value);
//         tokens->value = new_str;
//         tokens = tokens->next;
//     }  
// }

void    expand_value(char *str, char *new_str, t_env **g_env, t_trim *trim)
{
    char    *expanded;
    int     len;

    expanded = replace_env_vars(&str[trim->i], g_env, trim);
    len = ft_strlen(expanded);
    strncpy(&new_str[trim->j], expanded, len);
    trim->j += len;
    trim->i = trim->end_index;
    free(expanded);
}

char    *expand_var(char *str, t_env **g_env, t_trim *trim)
{
    char    *new_str;
    int     flag = 0;

    trim->i = 0;
    trim->j = 0;
    new_str = malloc(1024 * sizeof(char));
    if (!new_str)
        return (NULL);
    while (str[trim->i])
    {
        if (str[trim->i] == '$' && str[trim->i + 1] && (!trim->in_single || trim->c == 0))
        {
            flag = 1;
            if (str[trim->i + 1] == '?')
                interrogation(new_str, trim);
            else
                expand_value(str, new_str, g_env, trim);
        }
        else
        {
            new_str[trim->j] = str[trim->i];
            trim->j++;
        }
        trim->i++;
    }
    if (flag == 0)
    {
        new_str = ft_strdup(str);
        return (new_str);
    }
    new_str[trim->j] = '\0';
    return (new_str);
}

char    *process_token(char *str, t_env **g_env, t_trim *trim)
{
    char    *trimmed;
    char    *expanded;

    printf("str: %s\n", str);
    trimmed = trim_quotes(str, trim);
    printf("trimmed: %s\n", trimmed);
    expanded = expand_var(trimmed, g_env, trim);
    printf("expanded: %s\n", expanded);
    free(trimmed);
    return (expanded);
}

void    trim_tokens(t_list *tokens, t_env **g_env)
{
    t_trim  trim;
    char    *str;
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
