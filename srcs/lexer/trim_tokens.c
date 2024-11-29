/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 07:18:36 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/29 11:45:27 by marlonco         ###   ########.fr       */
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

void    remove_quotes(t_list *tokens, char  *str)
{
    char    *new_str;
    int     i;
    int     len;
    
    len = ft_strlen(str);
    new_str = malloc((len - 1) * sizeof(char));
    if (!new_str)
        return;
    i = 1;
    while (i < (len - 1))
    {
        new_str[i - 1] = str[i];
        i++;
    }
    new_str[len - 2] = '\0';
    free(tokens->value);
    tokens->value = new_str;
}

void    remove_quotes2(t_list *tokens, char *str)
{
    char    *new_str;
    int     i;
    int     j;
    int     len;

    i = 0;
    j = 0;
    len = ft_strlen(str);
    new_str = malloc((len - 1) * sizeof(char));
    if (!(new_str))
        return;
    while (str[i])
    {
        if (str[i] != '\'' && str[i] != '\"')
        {
            new_str[j] = str[i];
            j++;
        }
        i++;
    }
    new_str[j] = '\0';
    free(tokens->value);
    tokens->value = new_str;
}

void    refer_envv(t_list *tokens, int start, char **str)
{
    int         i;
    int         new_len;
    char        *envv; // the ref of $
    char        *new_str; // the new str in the token
    const char  *envv_value; // the vakue of the $ ref

    i = 0;
    while (str[start + i + 1]
            && !(is_space(*str[start + i + 1]))
            && *str[start + i + 1] != '$')
        i++;
    envv = malloc((i + 1) * sizeof(char));
    if (!envv)
        return;
    ft_memcpy(envv, &str[start + 1], i);
    envv[i] = '\0';
    envv_value = getenv(envv);
    free(envv);
    if (envv_value)
    {
        new_len = ft_strlen(*str) - i - 1 + ft_strlen(envv_value);
        new_str = malloc((new_len + 1) * sizeof(char));
        if (!new_str)
            return;
        ft_memcpy(new_str, str, start); // copy the beginning part of the tokens>value
        ft_memcpy((new_str + start), envv_value, ft_strlen(envv_value)); // copy the envv value
        ft_memcpy((new_str + start + ft_strlen(envv_value)), (str + start + i + 1), 
                        (ft_strlen(*str) - start - i)); // copy the remaining part of the str
        new_str[new_len] = '\0';
        free (tokens->value);
        tokens->value = new_str;
    }
    else 
        write (1, "\n", 1); // VERIFY THE BEHAVIOR ON MACS 
}

int singlequotes_count(char *str)
{
    int i;
    int count;
    
    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == '\'')
            count++;
        i++;
    }
    return (count);
}

int doublequotes_count(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == '\"')
            count++;
        i++;
    }
    return (count);
}

void    trim_tokens(t_list *tokens, t_env **env)
{
    int     i;
    char    *str;
    
    i = 0;

    if (!tokens || !(tokens->value))
        return;
    while (tokens)
    {
        str = (char *)tokens->value;
        if ((str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
                || (str[0] == '\'' && str[ft_strlen(str) - 1] == '\''))
        {
            remove_quotes(tokens, str);
            str = (char *)tokens->value;
        }
        else if (singlequotes_count(str) % 2 == 0
                   && doublequotes_count(str) % 2 == 0)
        {
            remove_quotes2(tokens, str);
            str = (char *)tokens->value;
        }
        else if (singlequotes_count(str) % 2 != 0
                    || doublequotes_count(str) % 2 != 0)
            return(error("We must not implement the dquote> functiunality :D\n"));
        i = 0;
        if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
        {
            while (str && str[i])
            {
                if (str[i] == '$' && str[i + 1])
                    refer_envv(tokens, i, &str);
                i++;
            }
        }
        tokens = tokens->next;
    }
}

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
//     trim_tokens(node1);

//     // After trimming
//     printf("\nAfter trimming:\n");
//     current = node1;
//     while (current) {
//         printf("Node value: %s\n", (char *)current->value);
//         current = current->next;
//     }

//     return 0;
// }
