/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:14:49 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/05 15:55:59 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    cd < ONLY ONE relative/absolute path>
    
    cd      --> go to home directory
    cd -    --> go to previous directory
    
    int chdir(const char *path) 
        --> returns 0 on success / -1 on error
        --> can directly interpret ".." as the parent dir
    char    *getcwd(char *buf, size_t size)
        --> buf = array where the current working dir path will be stored 
        --> size = the size of the buf 
        --> returns NULL on error 
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

void    update_envv(char *key, char *new_value)
{
    t_env   *var;
    
    var = find_key(key);
    if (var)
    {
        free(var->value);
        var->value = ft_strdup(new_value);
    }
}

static int  only_cd()
{
    t_env   *home_var;

    home_var = find_key("HOME");
    if (home_var && home_var->value)
    {
        if (chdir(home_var->value) != 0)
            return(perror("cd"), 1);
        update_envv("OLDPWD", find_key("PWD")->value);
        update_envv("PWD", home_var->value);
    }
    else
        return(ft_putstr_fd("cd: HOME not set\n", 2), 1);
    return (0);
}

static int  minus_cd()
{
    t_env   *oldpwd_var;

    oldpwd_var = find_key("OLDPWD");
    if (oldpwd_var && oldpwd_var->value)
    {
        if(chdir((const char *)oldpwd_var) != 0)
            return(perror("cd"), 1);
        update_envv("OLDPWD", find_key("PWD")->value);
        update_envv("PWD", oldpwd_var->value);
    }
    else
        return(ft_putstr_fd("cd: OLDPWD not set\n", 2), 1);
    return (0);
}

// to implement : tilde & variants ; symlinks ? 
static int  basic_cd(char *path)
{
    char    cwd[PATH_MAX];
    
    // storing the current directolry path
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return(perror("getcwd"), 1);
    // changing the directory to specified path
    if (chdir(path) != 0)
        return(perror("cd"), 1);
    // update oldpwd with previous path stored in cwd
    update_envv("OLDPWD", cwd);
    // update pwd  witgh the new cwd path
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        update_envv("PWD", cwd);
    else 
        return(perror("getcwd"), 1);
    return (0);
}

// RETURN ?
void    cd(char **argv)
{
    char    **input;

    // IMPLEMENT ERROR HANDLING
    input = &argv[1];
    if (list_size(input) > 1 || list_size(input) < 0)
        error("cd: more than 1 relative/absolute path");
    if (list_size(input) == 0)
        only_cd();
    else if (ft_strncmp(input[0], "-", INT_MAX))
        minus_cd();
    else
        basic_cd(input[0]);
}