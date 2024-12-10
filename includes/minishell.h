/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:59:52 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/10 16:41:35 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
#include <string.h>
#include <stddef.h>
#include <limits.h>
#include <dirent.h>
#include <stdbool.h> 
#include <signal.h>
#include <termios.h>
#ifndef S_ISLNK
#define S_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)
#endif

// ********** builtins **********
    //builtins
void    builtins(t_cmd *cmd);
    //cd
        //cd_utils
t_env   *find_key(char *key, t_env **env);
void    update_envv(char *key, char *new_value, t_env **env);
        //cd
void    cd(char **argv, t_env **env);
    //echo
int     echo(char **argv);
    //env
t_env   *init_envv(void);
void	env(t_env **env);
    //exit
void    ft_exit(char **argv, t_env **env);
    //export
int    export(char **argv, t_env **env);
    //pwd
int     pwd(void);
    //unset
void    unset(char **argv, t_env **env);
    //utils
int		is_space(char c);
int     ft_strcmp(const char *s1, const char *s2);
int     list_size(char **argv); // DO WE USE IT ?
void    remove_first(char **argv, int *size); // DO WE USE IT ?
// ********** exec **********
    //exec_cmd
void	ft_exec_cmd(t_cmd *cmd);
char	**ft_lst_to_matrice(t_env **g_env);
void	ft_free_matrice(char **matrice);
    //exec_pipe
void	ft_exec_pipe(t_pipe *node, int dupfd, int *cmd_index);
void	ft_dup2(int fd1, int fd2);
    //exec_redir
void	ft_exec_redir(t_redir *redir, int dupfd, int *cmd_index);
    //exec_ast
void	ft_exec(t_node *node, int dupfd, int *cmd_index);
void	ft_execute_ast(t_node *node);
    //check redir
void    ft_checkredir(t_redir *redir);
// ********** lexer **********
    //lexer_utils
void	ft_update_quotes_status(char c, int *d_quote_status, int *s_quote_status);
int	    ft_is_sp(char c, int *d_quote, int *s_quote);
char	*ft_get_token(char *s, int *i, int *d_quote, int *s_quote);

    //lexer
void	ft_lexer(char *str, t_list **tokens);
    //trim_tokens
    void trim_tokens(t_list *tokens, t_env **g_env);
    //error lexing
int ft_checklexing(t_list *token);
// ********** parser **********
    //ast
t_node	*ft_parsetoken(t_list **token, t_env **g_env, int *hd_index);
void    ast_printer(t_node *node, int level);
    //parse_cmd
t_node	*ft_cmdnode(char **argv, t_env **g_env, t_list **token);
char    **ft_getargv(t_list *token);
    //parse_pipe
t_node	*ft_pipenode(t_node *left, t_node *right, t_list **token);
t_list	*ft_get_prevpipe(t_list *token);
t_list	*ft_get_nextpipe(t_list *token);
    //parse_redir
int	    ft_strcmp2(char *str, char *str_to_find);
t_node	*ft_redirnode(char *file, t_node *cmd, int type, t_list **token);
int     ft_token_isredir(t_list *token);
t_list  *ft_get_prevredir(t_list *token);
char    *ft_get_file_and_type(t_list *token, int *type, int *hd_index, t_env **g_env);
// ********** signals **********
    //signals
void    handle_signals(void);
void handle_child_signals(void);
void ignore_sigint();
void	rl_replace_line(const char *text, int clear_undo);//readline lib
// ********** free_ast **********
void	ft_free_ast(t_node *node);
// ********** ft_error **********
void    ft_error(char *str);
void	ft_panic(char *str, char *name, int exit_code);
// ********** main **********
void	ft_printlst(t_list *e); // for debug
int	    ft_countheredocs(t_list *token);
void	ft_del_hdfiles();
void    ft_pars_and_exec(char *prompt, t_env **g_env);
// ********** utils **********
void    error(const char *error);
void    free_str(char *str);
void    free_env(t_env *env);
void    free_array(char **array);
char    *ft_getenv(char *name, t_env **g_env);
// ********** utils2 **********
char	*ft_itoa(int nbr);
//crash test functions
int  ft_isbuiltins(t_node *node);

//utils :)
void ft_stats(int pid);
#endif