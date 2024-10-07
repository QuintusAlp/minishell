/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:59:52 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/07 12:46:46 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
//error
void ft_error(char *str);
//parsing
void ft_parsing(char *prompt);
t_list *ft_lexer(char *str);
void	*ft_ast_builder(t_list *token);
//for debug
void	ft_printlst(t_list *e);
//ast functions
// pipe
t_list	*ft_get_prevpipe(t_list *token);
t_list	*ft_get_nextpipe(t_list *token);
t_node	*ft_pipenode(t_node *left, t_node *right, t_list *token);
// redir
t_node	*ft_redirnode(t_node *cmd, char *file, int type, t_list *token);
t_list *ft_get_prevredir(t_list *token);
char *ft_get_file(t_list *token);
// cmd
t_node	*ft_cmdnode(char **argv, char **env, t_list *token);
char **ft_getargv(t_list *token);
#endif
