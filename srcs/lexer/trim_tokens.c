/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 07:18:36 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/01 20:38:32 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
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

static char *trim_quotes(char *str, bool *in_single_quotes, bool *in_double_quotes, bool *single_inside_double, int *c)
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
        if (str[i] == '\'' && *in_double_quotes)
            *in_single_quotes = !(*in_single_quotes);
        else if (str[i] == '\"' && (*in_single_quotes))
            *in_double_quotes = !(*in_double_quotes);
        else if (str[i] == '\'' && *in_double_quotes)
            *single_inside_double = 1;
        else 
            result[j++] = str[i];
        if (str[i] == '\'')
            *c += 1;
        printf("%c, %d, single quotes flag: %i, double quotes flag: %i, single in doubles flag: %i\n", str[i], i, *in_single_quotes, *in_double_quotes, *single_inside_double);
        i++;
    }
    result[j] = '\0';
    printf("result trim tokens: %s\n", result);
    return (result);
}

char *replace_env_vars(char *str, t_env **g_env, int *end_index) {
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
    var_name = ft_strndup(&str[1], i - 1); // with j the position where the env name ends, i the position of $ and not including j 
    printf("var name: %s\n", var_name);
    env_value = ft_getenv(var_name, g_env);
    printf("env value: %s\n", env_value);
    free(var_name);
    if (!env_value)
        new_str = ft_strdup("");
    else 
        new_str = ft_strdup(env_value);
    *end_index = i;
    return (new_str);
}

void trim_tokens(t_list *tokens, t_env **g_env) {
    char *str;
    char *new_str;
    int  i;
    int  j;
    int c;
    int end_index;
    bool in_single_quotes;
    bool    in_double_quotes;
    bool    single_inside_double;

    i = 0;
    j = 0;
    c = 0;
    in_single_quotes = 1;
    in_double_quotes = 1;
    single_inside_double = 0;
    while (tokens) 
    {
        str = (char *)tokens->value;
        printf("str: %s\n",  str);
        str = trim_quotes(str, &in_single_quotes, &in_double_quotes, &single_inside_double, &c);
        new_str = malloc(1024 * sizeof(char));
        if (!new_str)
            return;
        i = 0;
        j = 0;
         while (str[i])
         {
            if (str[i] == '$' && str[i + 1] && (!(in_single_quotes) || c == 0 || 
                single_inside_double))
            {
                printf("LAAAAAAA\n");
                char *expanded = replace_env_vars(&str[i], g_env, &end_index);
                printf("expanded: %s\n", expanded);
                strncpy(&new_str[j], expanded, ft_strlen(expanded));
                j += ft_strlen(expanded);
                free(expanded);
                i += end_index - 1;
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
