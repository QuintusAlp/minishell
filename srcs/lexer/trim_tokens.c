/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 07:18:36 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/07 17:26:46 by qalpesse         ###   ########.fr       */
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

void    remove_quotes(t_list *tokens)
{
    char    *new_str;
    int     i;
    
    new_str = malloc(ft_strlen(tokens->value) - 1);
    if (!new_str)
        return;
    i = 1;
    while (i < (ft_strlen(tokens->value)))
    {
        new_str[i - 1] = (char)tokens->value[i]; // ICI
        i++;
    }
    new_str[i] = '\0';
    free(tokens->value);
    tokens->value = new_str;
}

void    refer_envv(t_list *tokens, int start)
{
    int         i;
    int         j;
    char        *envv;
    char        *new_str;
    const char  *envv_value;

    i = 0;
    j = 0;
    while (!(is_space((char *)tokens->value[start + i])))
        i++;
    envv = malloc((i - start) * sizeof(char));
    if (!envv)
        return;
    ft_memcpy(envv, &tokens->value[start + 1], i);
    envv[i] = '\0';
    envv_value = get_env(envv);
    if (envv_value)
    {
        i = 0;
        new_str = malloc(ft_strlen(tokens->value) - (ft_strlen(envv) + 1) + ft_strlen(envv_value) + 1 
                            * sizeof(char));
        if (!new_str)
            return;
        while (i < start)
        {
            new_str[i] = (char *)tokens->value[i];
            i++;
        }
        while (envv_value[j])
        {
            new_str[i] = envv_value[j];
            i++;
            j++;
        }
        while (&tokens->value[i])
        {
            new_str[i] = envv_value[i];
            i++;
        }
        free (tokens->value);
        tokens->value = new_str;
    }
    else 
        // print a newline but how to properly do this 
}

void    trim_tokens(t_list *tokens)
{
    int i;

    i = 0;
    if (!tokens || !(tokens->value))
        return;
    while (tokens)
    {
        char *str = (char *)tokens->value;// la ca marche !!!!! pcw (char *)str[0] -> tu esssayes de cast un char en address
        if ((str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
                || (str[0] == '\'' && str[ft_strlen(str) - 1] == '\''))
            remove_quotes(tokens);
        i = 0;
        while (&str[i])
        {
            if (str[i] == '$' && &str[i + 1])
                refer_envv(tokens, i);
            i++;
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

//     node3->value = strdup("NoQuotesHere");
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

//     // Free allocated memory
//     free(node1->value);
//     free(node2->value);
//     free(node3->value);
//     free(node1);
//     free(node2);
//     free(node3);

//     return 0;
// }
