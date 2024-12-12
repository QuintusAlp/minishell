/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 07:18:36 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/12 16:52:31 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void    cases(char *str,char *new_str, t_trim *trim, t_env **g_env)
{
    if (str[trim->i] == '$' && str[trim->i + 1] && (!trim->in_single || trim->c == 0))
    {
        trim->flag = 1;
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
}

char    *expand_var(char *str, t_env **g_env, t_trim *trim)
{
    char    *new_str;

    trim->i = 0;
    trim->j = 0;
    new_str = malloc(1024 * sizeof(char));
    if (!new_str)
        return (NULL);
    while (str[trim->i])
    {
        cases(str, new_str, trim, g_env);
        trim->i++;
    }
    if (trim->flag == 0)
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

    trimmed = trim_quotes(str, trim);
    expanded = expand_var(trimmed, g_env, trim);
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