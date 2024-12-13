/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_tokensv2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:59:12 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/13 15:19:27 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *process_interrogation(t_trim *trim)
{
    char    *exitcode_str;
    
    exitcode_str = ft_itoa(g_exitcode);
    if (trim->flag == 1)
        return(exitcode_str);
    else
    {
        ft_strjoin(trim->new_str, exitcode_str);
        free(exitcode_str);
        return (NULL);
    }
}

void    process_dollar(char *str, t_trim *trim, t_env **g_env)
{
    char    *tmp;
    
    trim->k = trim->i + 1;
    if (!str[trim->k])
        ft_strjoin(trim->new_str, "$"); // juste print $
    while (str[trim->k])
    {
        while (str[trim->k] != '$')
            trim->k++;
        if (str[trim->k] == '?')
            process_interrogation(trim);
        else 
        {
            tmp = ft_strndup(&str[1], (trim->k - trim->i));
            replace_env_vars(tmp, trim, g_env);
            free(tmp);
        }
        trim->k++;
    }
}

void    process_singles(char *str, t_trim *trim)
{
    char    *tmp;
    char    *tmp2;
    
    trim->k = 1;
    while (str[trim->k] != '\'' && str[trim->k])
        trim->k++;
    tmp = ft_strndup(&str[1], (trim->k - 1));
    tmp2 = ft_strdup(trim->new_str);
    trim->new_str = ft_strjoin(tmp2, tmp);
    trim->i += ft_strlen(tmp) + 2;
    trim->j += ft_strlen(tmp);
    free(tmp);
    free(tmp2);
}

void    process_doubles(char *str, t_trim *trim, t_env **g_env)
{
    char    *tmp;
    char    *tmp2;

    trim->k = 1;
    while (str[trim->k] != '\"' && str[trim->k])
        trim->k++;
    tmp = ft_strndup(&str[1], (trim->k - 1));  
    if (ft_strchr (tmp, '$') != NULL)
        process_dollar(tmp, trim, g_env);
    tmp2 = ft_strdup(trim->new_str);
    trim->new_str = ft_strjoin(tmp2, tmp);
    trim->i += ft_strlen(tmp) + 2;
    trim->j += ft_strlen(tmp);
    free(tmp);
    free(tmp2);
}

char    *process_token(char *str, t_env **g_env, t_trim *trim)
{
    if (ft_strchr(str, '$') == NULL && ft_strchr(str, '\'') == NULL
            && ft_strchr(str, '\"') == NULL)
        return (ft_strdup(str));
    while (str[trim->i])
    {
        
        if (str[trim->i] == '\"')
            process_doubles(&str[trim->i], trim, g_env);
        else if (str[trim->i] == '\'')
            process_singles(&str[trim->i], trim);
        else if (str[trim->i] == '$' && str[trim->i + 1])
            process_dollar(&str[trim->i], trim, g_env);
        else
        {
            printf("else: i=%d, str: %c\n", trim->i, str[trim->i]);
            trim->new_str[trim->j++] = str[trim->i++];
        } 
        printf("new_str: %s, i: %d, j: %d\n", trim->new_str, trim->i, trim->j);
        trim->new_str[trim->j] = '\0';
    }
    printf("new str en dehors du loop: %s\n", trim->new_str);
    return (trim->new_str);
}

void    init_trim(t_trim *trim)
{
    trim->in_double = 0;
    trim->in_single = 0;
    trim->c = 0;
    trim->end_index = 0;
    trim->j = 0;
    trim->i = 0;
    trim->k = 0;
    trim->flag = 0;
    trim->new_str = ft_strdup("");
    trim->temp = ft_strdup("");
}

void    trim_tokensv2(t_list *tokens, t_env **g_env)
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
        printf("current token value: %s\n", (char *)current->value);
        current = current->next;
    }
}