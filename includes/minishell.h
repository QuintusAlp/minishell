/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:59:52 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/15 15:30:43 by qalpesse         ###   ########.fr       */
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
//error
void ft_error(char *str);
//parsing
void ft_pars_and_exec(char *prompt, char **env);
t_list *ft_lexer(char *str);
//for debug
void	ft_printlst(t_list *e);
void ast_printer(t_node *node, int level);
//ast functions
t_node	*ft_parsetoken(t_list *token, char **env);
// pipe
t_list	*ft_get_prevpipe(t_list *token);
t_list	*ft_get_nextpipe(t_list *token);
t_node	*ft_pipenode(t_node *left, t_node *right, t_list *token);
// redir
t_node	*ft_redirnode(t_node *cmd, char *file, int type, t_list *token);
t_list *ft_get_prevredir(t_list *token);
char *ft_get_file_and_type(t_list *token, int *type);
// cmd
t_node	*ft_cmdnode(char **argv, char **env, t_list *token);
char **ft_getargv(t_list *token);
int ft_token_isredir(t_list *token);
//free ast
void	ft_free_ast(t_node *node);

//execute ast
void	ft_execute_ast(t_node *node);
void ft_exec(t_node *node, int *pipefd, int dupfd, int *cmd_index);
// exec pipe
void	ft_exec_pipe(t_pipe *node, int dupfd, int *cmd_index);
// exec cmd
void	ft_exec_cmd(t_cmd *cmd, int *pipefd, int dupfd, int *cmd_index);
// exec redir
void ft_exec_redir(t_redir *redir);

#endif
