/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:19:46 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/28 19:39:01 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// function to convert a chaines list into a table of table (char **)

int row_count(t_env *env)
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

void    free_rows(char **table, int i)
{
    int j;

    j = 0;
    while (j < i)
    {
        free(table[j]);
        free(table);
        j++;
    }
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
        char **row = malloc(4 * sizeof(char *));
        if (!row)
            return(free_rows(table, i), NULL);
        row[0] = strdup(current->name);
        row[1] = strdup(current->value);
        row[2] = strdup(ft_atoi(current->index));
        row[3] = NULL;
        table[i++] = row;
        current = current->next;
    }
    table[i] = NULL;
    return (table);
}