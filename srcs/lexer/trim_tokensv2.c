/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_tokensv2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:59:12 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/17 16:55:29 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    add_to_newstr(char *str, t_trim *trim)
{
    char    *tmp;
    
    tmp = trim->new_str;
    trim->new_str = ft_strjoin(tmp, str);
    free (tmp);
}
char *process_interrogation(char *str, t_trim *trim)
{
    char    *exitcode_str;
    char    *tmp;
    char    *result;
   int     i;

    printf("str: %s k dans ?: %d\n", str, trim->k);
    i = 1;
    tmp = malloc(ft_strlen(str) * sizeof(char));
    if (!tmp)  
        return (NULL);
    exitcode_str = ft_itoa(g_exitcode);
    if (str[1])
    {
        printf("yooooo\n");
        while (str[i])
        {
            tmp[i - 1] = str[i];     
            i++;
        }
        tmp[i - 1] = '\0';
    }
    printf("temp: %s\n", tmp);
    result = ft_strjoin(exitcode_str, tmp);
    free(exitcode_str);
    free(tmp);
    printf("result process ?: %s\n", result);
    return (result);
}

void    process_dollar(char *str, t_trim *trim, t_env **g_env)
{
    char    *tmp;
    char    *result;
    int     i;
    
    printf("into $: %s\n", str);
    trim->k = 1;
    i = 0;
    tmp = ft_strdup("");
    while (str[trim->k])
    {
        i = 0;
        while (str[trim->k] != '$' && str[trim->k])
            tmp[i++] = str[trim->k++];
        printf("tmp: %s, k after tm: %d\n", tmp, trim->k);
        printf("tmp[0]: %c\n", tmp[0]);
        if (tmp[0] == '?')
        {
            result = ft_strdup(process_interrogation(tmp, trim)); 
            printf("apres ? trimk: %d\n", trim->k);
            add_to_newstr(result, trim);
            trim->j += ft_strlen(result);
            trim->k += ft_strlen(tmp);
            //free (result);
        }
        else 
        {
            printf("string sent into replace env: %s\n",&str[trim->k]);
            result = ft_strdup(replace_env_vars(&str[trim->k], trim, g_env));
        }
        free(tmp);
        //trim->k++;
    }
    printf("result process $: %s\n", result);
    trim->i += ft_strlen(str);
    //free (result);
    printf("new str after strjon: %s\n", trim->new_str);
}

void    process_singles(char *str, t_trim *trim)
{
    char    *tmp;
    
    trim->k = 1;
    while (str[trim->k] != '\'' && str[trim->k])
        trim->k++;
    tmp = ft_strndup(&str[1], (trim->k - 1));
    add_to_newstr(tmp, trim);
    trim->i += ft_strlen(tmp) + 2;
    trim->j += ft_strlen(tmp);
    free(tmp);
}

void    process_doubles(char *str, t_trim *trim, t_env **g_env)
{
    char    *tmp;
    char    *result;
    int     i;

    result = ft_strdup("");
    trim->k = 1;
    while (str[trim->k] && str[trim->k] != '\"')
        trim->k++;
    tmp = ft_strndup(&str[1], (trim->k - 1));  
    if (ft_strchr (tmp, '$') != NULL)
    {
        i = 0;
        while (tmp[i] && tmp[i] != '$')
        {
            result[i] = tmp[i];
            i++;
            trim->i++;
        }
        add_to_newstr(result, trim);
        process_dollar(&tmp[i], trim, g_env);
        trim->i += 2;
        trim->j += ft_strlen(result);
        return ;
    }
    printf("tmp dans process doubles: %s\n", tmp);
    add_to_newstr(tmp, trim);
    printf("new str procces doubles: %s\n", trim->new_str);
    trim->i += ft_strlen(tmp) + 2;
    trim->j += ft_strlen(tmp);
    free(tmp);
}


char    *process_token(char *str, t_env **g_env, t_trim *trim)
{
    if (ft_strchr(str, '$') == NULL && ft_strchr(str, '\'') == NULL
            && ft_strchr(str, '\"') == NULL)
        return (ft_strdup(str));
    while (str[trim->i])
    {
        
        if (str[trim->i] == '\"')
        {
            process_doubles(&str[trim->i], trim, g_env);
            printf("i apres process doubles dans grande fct: %d\n", trim->i);
        }
        else if (str[trim->i] == '\'')
        {
            process_singles(&str[trim->i], trim);
            printf("i apres process singles dans grande fct: %d\n", trim->i);
        }
        else if (str[trim->i] == '$' && str[trim->i + 1])
        {
            process_dollar(&str[trim->i], trim, g_env);
            printf("i apres process $ dans grande fct: %d\n", trim->i);
        }
        else
        {
            printf("else: i=%d, str: %c\n", trim->i, str[trim->i]);
            trim->new_str[trim->j++] = str[trim->i++];
        } 
        printf("new_str: %s, i: %d, j: %d\n", trim->new_str, trim->i, trim->j);
        trim->new_str[trim->j] = '\0';
    }
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
