/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:14:49 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/06 18:39:36 by marlonco         ###   ########.fr       */
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
    DIR     *opendir(const char *name)
        --> name = path of the dir i want to open 
            --> returns NULL on error or a ptr used to access the dir's content 
        --> once open succesfully: readdir
        --> once read: closedir 
    struct dirent
        struct dirent {
            ino_t d_ino;             // Inode number (unique identifier for the file)
            off_t d_off;             // Offset to the next dirent structure
            unsigned short d_reclen; // Length of this record (structure)
            unsigned char d_type;    // Type of file (e.g., regular file, directory, symlink)
            char d_name[256];        // Name of the file (or directory) in the entry
        };
    int     stat(const char *pathname, struct stat *statbuf)
        --> pathname = dir whose information to retrieve 
        --> statbuf = a struct stat that will be filled with the info about the file 
    struct stat {
    dev_t     st_dev;     ID of device containing file
    ino_t     st_ino;      Inode number 
    mode_t    st_mode;     File type and mode (permissions) 
    nlink_t   st_nlink;    Number of hard links 
    uid_t     st_uid;      User ID of owner 
    gid_t     st_gid;      Group ID of owner 
    dev_t     st_rdev;     Device ID (if special file) 
    off_t     st_size;     Total size, in bytes 
    blksize_t st_blksize;  Block size for file system I/O 
    blkcnt_t  st_blocks;   Number of 512B blocks allocated 
     Times: seconds since epoch 
    time_t    st_atime;    Last access time 
    time_t    st_mtime;    Last modification time 
    time_t    st_ctime;    Last status change time 
     Padding to prevent structure from being misaligned 
    long      __pad[3];
    }
    int access      (const char *pathname, int mode);
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

static int  tilde_cd(char *path)
{
    char            cwd[PATH_MAX];
    DIR             *dir;
    struct dirent   *dp;
    struct stat     file_stat;
    char            *path_user[INT_MAX];
    
    // option 1: only cd ~ or cd ~/ --> acts like cd
    if (strcmp(path, "~") == 0 || strcmp(path, "~/") == 0)
        return (only_cd());
    //option 2: ~/subdir --> go to subdir in the current user's home directory
    else if (strncmp(path, "~/", 2) == 0 && ft_strlen(path) > 2)
    {
        only_cd();
        return (basic_cd(&path[2]));
    }
    // ~otheruser --> go to the home of the other user 
    else if (strncmp(path, "~", 1) == 0 && ft_strlen(path) > 1)
    {
        // if linux 
        dir = opendir("/home/");
        ft_strlcpy(path_user, "/home/", 6); // 6 OR 7 ??
        ft_strlcat(path_user, &path[1], (ft_strlen(path_user) + ft_strlen(&path[1])));
        // if mac 
        dir = opendir("/Users/");
        ft_strlcpy(path_user, "/Users/", 7); // 7 OR 8 ??
        ft_strlcat(path_user, &path[1], (ft_strlen(path_user) + ft_strlen(&path[1])));
        
        if (dir == NULL)
            return(perror("Unable to read directory"), 0);
        while ((dp = readdir(dir)) != NULL)
        {
            if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
                continue;
            if (strcmp(dp->d_name, &path[1]) == 0) // si le argv est bien un username
            {
                if (stat(path_user, &file_stat) == -1) 
                    return(perror("stat"), 1);
                if (S_ISDIR(file_stat.st_mode)) // si le username est bien un dir
                {
                    if (access(&path[1], X_OK) == 0)
                    {
                        basic_cd(path_user);
                        return (0);
                    }
                    else
                        return (perror("Access error"), 1);
                } 
                return (1);
            }
        }
        closedir(dir);
        return (0);
    }
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
    else if (ft_strncmp(input[0], "-", INT_MAX) == 0)
        minus_cd();
    // else if (ft_strncmp(input[0][0], "~", 1) == 0)
    //     tilde_cd(input[0]);
    else
        basic_cd(input[0]);
}