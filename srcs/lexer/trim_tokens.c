/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 07:18:36 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/28 16:40:46 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    ft_strlcpy(char *dest, const char *src, size_t dstsize)
    typedef struct s_list
	{
		void			*value;
		int				type;
		struct s_list	*next;
	}	t_list;

    1) enlever les " / ' si le string commence et finit par ca
        --> si il ne commence/finit que avec ' : quote>
                                             " : dquote>
    2) remplacer $<VAR> par le contenu de la envv correspondante
*/
int ft_varlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0' && str[i] != ' ')
        i++;
    return (i);
}
char *ft_getvar(t_env *g_env, char *var)
{
    while(g_env)
    {
        if (!ft_strncmp(g_env->name, var, ft_strlen(g_env->name)))
        {
            return (ft_strdup(g_env->value));
        }
        g_env = g_env->next;
    }
    return (NULL);
}
char * ft_expender(char *str, t_env *g_env)
{
    char *substr;
    char *var;

    substr = NULL;
    (void)g_env;
    var = NULL;
    while (*str)
    {
        // printf("%c", *str);
        if (*str == '$')
        {
            var = malloc(ft_varlen(str + 1) + 1);
            ft_strlcpy(var, str + 1, ft_varlen(str + 1) + 1);
            //printf("value: %s\n", ft_getvar(g_env, var));
            str += ft_varlen(str + 1) + 1;
        }
        str++;
    }
    
    return (substr);
}
void    ft_trimmer(t_list *tokens, t_env *g_env)
{
    printf("trimer\n");
    while (tokens)
    {
        tokens->value = ft_expender(tokens->value, g_env);
        tokens = tokens->next;
    }
    
}
