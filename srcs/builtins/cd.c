/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:14:49 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/04 19:44:06 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    cd < ONLY ONE relative/absolute path>
    
    cd      --> go to home directory
    cd -    --> go to previous directory
    
    int chdir(const char *path) --> returns 0 on success / -1 on error
*/

t_env   *find_key(char *key)
{
    t_env *current;

    current = g_env;
    if (!key || !current)
        return (NULL);
    while (current)
    {
        if (ft_strncmp(current->name, key, INT_MAX) == 0)
            return (current);
        current = current->next;
    }
    return (NULL);
}

static int  only_cd()
{
    t_env   *home_var;

    home_var = find_key("HOME");
    if (home_var && home_var->value)
    {
        if (chdir(home_var->value) != 0)
            return(perror("cd"), 1);
    }
    else
        return(ft_putstr_fd(2, "cd: HOME not set\n"), 1);
    return (0);
}

static int  basic_cd(char *path)
{
    if (chdir(path) != 0)
        return(perror("cd"), 1);
    return (0);
}

static int  minus_cd()
{
    t_env   *oldpwd_var;

    oldpwd_var = find_key("OLDPWD");
    if (oldpwd_var && oldpwd_var->value)
    {
        if(chdir(oldpwd_var) != 0)
            return(perror("cd"), 1);
    }
    else
        return(ft_putstr_fd(2, "cd: OLDPWD not set\n", 1));
    return (0);
}

void    cd(char **argv)
{
    char    **input;

    // IMPLEMENT ERROR HANDLING
    input = &argv[1];
    if (list_size(input) > 2 || list_size(input) < 0)
        error("cd: more than 1 relative/absolute path");
    else if (list_size(input) == 0)
        only_cd();
    else if (list_size(input) == 1)
        basic_cd(input[0]);
    else if (list_size(input) == 2 && ft_strncmp(input[0], "-", INT_MAX))
        minus_cd();
    else
        return;
}