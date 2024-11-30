/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 07:18:36 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/30 14:20:36 by marlonco         ###   ########.fr       */
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

// void    remove_quotes(t_list *tokens, char  *str)
// {
//     char    *new_str;
//     int     i;
//     int     len;
    
//     len = ft_strlen(str);
//     new_str = malloc((len - 1) * sizeof(char));
//     if (!new_str)
//         return;
//     i = 1;
//     while (i < (len - 1))
//     {
//         new_str[i - 1] = str[i];
//         i++;
//     }
//     new_str[len - 2] = '\0';
//     free(tokens->value);
//     tokens->value = new_str;
// }

// void    remove_quotes2(t_list *tokens, char *str)
// {
//     char    *new_str;
//     int     i;
//     int     j;
//     int     len;

//     i = 0;
//     j = 0;
//     len = ft_strlen(str);
//     new_str = malloc((len - 1) * sizeof(char));
//     if (!(new_str))
//         return;
//     while (str[i])
//     {
//         if (str[i] != '\'' && str[i] != '\"')
//         {
//             new_str[j] = str[i];
//             j++;
//         }
//         i++;
//     }
//     new_str[j] = '\0';
//     free(tokens->value);
//     tokens->value = new_str;
// }

// void    refer_envv(t_list *tokens, int start, char **str, t_env **env)
// {
//     int         i;
//     int         new_len;
//     char        *envv; // the ref of $
//     char        *new_str; // the new str in the token
//     const char  *envv_value; // the value of the $ ref
//     (void)env;

//     i = 0;
//     printf("ICI\n");
//     while ((*str)[start + i + 1]
//             && !(is_space((*str)[start + i + 1]))
//             && (*str)[start + i + 1] != '$'
//             && (*str)[start + i + 1] != '\'')
//         i++;
//     envv = malloc((i + 1) * sizeof(char));
//     if (!envv)
//         return;
//     ft_memcpy(envv, &(*str)[start + 1], i);
//     envv[i] = '\0';
//     printf("Envv str: %s\n", envv);
//     envv_value = getenv(envv);
//     printf("getenv result: %s\n", envv_value);
//     free(envv);
//     if (envv_value && ft_strncmp(envv_value, (const char *)"(null)", ft_strlen("(null)")) != 0)
//     {
//         new_len = ft_strlen(*str) - i - 1 + ft_strlen(envv_value);
//         new_str = malloc((new_len + 1) * sizeof(char));
//         if (!new_str)
//             return;
//         ft_memcpy(new_str, *str, start); // copy the beginning part of the tokens>value
//         ft_memcpy((new_str + start), envv_value, ft_strlen(envv_value)); // copy the envv value
//         ft_memcpy((new_str + start + ft_strlen(envv_value)), (*str + start + i + 1), 
//                         (ft_strlen(*str) - start - i)); // copy the remaining part of the str
//         new_str[new_len] = '\0';
//         free (tokens->value);
//         tokens->value = new_str;
//         *str = tokens->value;
//     }
//     else 
//         write (1, "HELOOOO\n", 1); // VERIFY THE BEHAVIOR ON MACS 
// }

// int singlequotes_count(char *str)
// {
//     int i;
//     int count;
    
//     i = 0;
//     count = 0;
//     while (str[i])
//     {
//         if (str[i] == '\'')
//             count++;
//         i++;
//     }
//     return (count);
// }

// int doublequotes_count(char *str)
// {
//     int i;
//     int count;

//     i = 0;
//     count = 0;
//     while (str[i])
//     {
//         if (str[i] == '\"')
//             count++;
//         i++;
//     }
//     return (count);
// }

// void    trim_tokens(t_list *tokens, t_env **g_env)
// {
//     int     i;
//     char    *str;
//     int     flag;
    
//     i = 0;
//     flag = 0;
//     if (!tokens || !(tokens->value))
//         return;
//     while (tokens)
//     {
//         str = (char *)tokens->value;
//         printf("str: %s\n", str);
//         if ((str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
//                 || (str[0] == '\'' && str[ft_strlen(str) - 1] == '\''))
//         {
//             if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
//                 flag = 1;
//             remove_quotes(tokens, str);
//             str = (char *)tokens->value;
//         }
//         else if (singlequotes_count(str) % 2 == 0
//                    && doublequotes_count(str) % 2 == 0)
//         {
//             remove_quotes2(tokens, str);
//             str = (char *)tokens->value;
//         }
//         else if (singlequotes_count(str) % 2 != 0
//                     || doublequotes_count(str) % 2 != 0)
//             return(error("We must not implement the dquote> functiunality :D\n"));
//         i = 0;
//         if (flag != 1)
//         {
//             while (str && str[i])
//             {
//                 if (str[i] == '$' && str[i + 1])
//                     refer_envv(tokens, i, &str, g_env);
//                 i++;
//             }
//         }
//         tokens = tokens->next;
//     }
// }

// int main() {
//     // Creating test data
//     t_list *node1 = malloc(sizeof(t_list));
//     t_list *node2 = malloc(sizeof(t_list));
//     t_list *node3 = malloc(sizeof(t_list));

//     // Initialize node values (with quotes to test removal)
//     node1->value = strdup("\"Hello, World!\"");
//     node1->type = 0;
//     node1->next = node2;

//     node2->value = strdup("'Goodbye!'");
//     node2->type = 0;
//     node2->next = node3;

//     node3->value = strdup("Voici le envv user : $USER");
//     node3->type = 0;
//     node3->next = NULL;

//     // Before trimming
//     printf("Before trimming:\n");
//     t_list *current = node1;
//     while (current) {
//         printf("Node value: %s\n", (char *)current->value);
//         current = current->next;
//     }

//     // Trim tokens (remove quotes)
//     trim_tokens(node1, env);

//     // After trimming
//     printf("\nAfter trimming:\n");
//     current = node1;
//     while (current) {
//         printf("Node value: %s\n", (char *)current->value);
//         current = current->next;
//     }

//     return 0;
// }



// // Helper to count occurrences of a character
// int count_char(char *str, char c) {
//     int count = 0;
//     while (*str) {
//         if (*str == c) count++;
//         str++;
//     }
//     return count;
// }

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
    int in_single_quote;
    int in_double_quote;
    int  i;
    int  j;
    int end_index;

    in_single_quote = 0;
    in_double_quote = 0;
    i = 0;
    j = 0;
    while (tokens) {
        str = (char *)tokens->value;
        printf("str: %s\n",  str);
        new_str = malloc(1024 * sizeof(char));
        if (!new_str)
            return;
        i = 0;
        j = 0;
        while (str[i]) 
        {
            printf("str[%d]: '%c'\n", i, str[i]);
            if (str[i] == '\'' && !in_double_quote)
                in_single_quote = !in_single_quote;
            else if (str[i] == '"' && !in_single_quote)
                in_double_quote = !in_double_quote;
            if (str[i] == '$' && str[i + 1] && !in_single_quote)
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
        if (in_single_quote || in_double_quote)
        {
            printf("Error: Unmatched quotes in command\n"); // CHANGER POR PRINT ON 2
            return;
        }
        tokens = tokens->next;
    }
}
