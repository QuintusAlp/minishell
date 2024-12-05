/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:19:46 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/05 16:12:17 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// function to convert a chaines list into a table of table (char **)

static int row_count(t_env *env)
{
    int     i;
    t_env   *current;

    i = 0;
    current = env;
    while (current)
    {
        i++;
        current = current->next;
    }
    return (i);
}

static void    free_rows(char **table, int i)
{
    int j;

    j = 0;
    while (j < i)
    {
        if (table[j])
        {
            free(table[j][0]);
            free(table[j]);
        }
        j++;
    }
    free(table);
}

char **list_converter(t_env *env)
{
    int     i;
    char    **table;
    t_env   *current;

    i = 0;
    if (!env)
        return (NULL);
    table = malloc ((row_count(env) + 1) * sizeof(char **));
    if (!table)
        return (NULL);
    current = env;
    while (current)
    {
        if (!current->name)
            table[i] == NULL;
        else 
        {
            table[i] = malloc(4 * sizeof(char *));
            if (!table[i])
                return(free_rows(table, i), NULL);
            table[i][0] = strdup(current->name);
            table[i][1] = strdup(current->value);
            table[i][2] = strdup((char *)(current->index));
            table[i][3] = NULL;
            i++;
            current = current->next;
        }
    }
    table[i] = NULL;
    return (table);
}
