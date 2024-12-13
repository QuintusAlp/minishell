/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_tokens_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:50:04 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/13 12:13:13 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    process_dollar
    /         \     
   /           \         
process ?       expand_value
                     |
                replace_env_vars   
*/

char *replace_env_vars(char *str, t_trim *trim, t_env **g_env) 
{
    char    *new;
    char    *env_value;
    char    *var_name;
    int     i;

    i = 0;
    if (!str[i] || !str[i + 1] || !(ft_isalnum(str[i + 1])))
        return (NULL);
    i++;
    while (str[i] && (isalnum(str[i]) || str[i] == '_' || str[i] == '$')) 
        i++;
    var_name = ft_strndup(&str[1], i - 1);
    env_value = ft_getenv(var_name, g_env);
    free(var_name);
    if (!env_value)
        new = ft_strdup("");
    else 
        new = ft_strdup(env_value);
    if (trim->flag == 1)
        return (new);
    else 
    {
        ft_strjoin(trim->new_str, new);
        free (new);
    }
    return (NULL);
}


// void    expand_value(char *str, t_trim **trim, t_env **g_env)
// {
    
// }