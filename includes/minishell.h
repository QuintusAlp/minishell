/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:59:52 by qalpesse          #+#    #+#             */
/*   Updated: 2024/11/05 14:32:15 by qalpesse         ###   ########.fr       */
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
//error
void ft_error(char *str);
void	ft_panic(char *str, char *name, int exit_code);
//parsing
void	ft_del_hdfiles(int nbr_heredoc);
void ft_pars_and_exec(char *prompt, char **env);
void	ft_lexer(char *str, t_list **tokens);
//count heredocs
int	ft_countheredocs(t_list *token);
// lexer utils
void	ft_update_quotes_status(char c, int *d_quote_status, int *s_quote_status);
int	ft_is_sp(char c, int *d_quote, int *s_quote);
char	*ft_get_token(char *s, int *i, int *d_quote, int *s_quote);
//for debug
void	ft_printlst(t_list *e);
void ast_printer(t_node *node, int level);
//ast functions
t_node	*ft_parsetoken(t_list **token, char **env, int *hd_index);
// pipe
t_list	*ft_get_prevpipe(t_list *token);
t_list	*ft_get_nextpipe(t_list *token);
t_node	*ft_pipenode(t_node *left, t_node *right, t_list **token);
// redir
t_node	*ft_redirnode(char *file, t_node *cmd, int type, t_list **token);
t_list *ft_get_prevredir(t_list *token);
char *ft_get_file_and_type(t_list *token, int *type, int *hd_index, char **env);
int	ft_strcmp(char *str, char *str_to_find);
// cmd
t_node	*ft_cmdnode(char **argv, char **env, t_list **token);
char **ft_getargv(t_list *token);
int ft_token_isredir(t_list *token);
//free ast
void	ft_free_ast(t_node *node);
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include <limits.h>

typedef struct s_env {
	char			*name;
	char			*value;
	int				index;
	struct s_env	*next;
}	t_env;

t_env   *g_env;

 typedef struct s_cmd	
{
	int		type;
	char 	**argv;
	//char 	**env;
}	t_cmd;

enum e_char_token
{
	PIPE,
	WORD,
	I_REDIR,
	O_REDIR_APPEND,
	O_REDIR_TRUNC,
	HEREDOC,
	REDIR,
	CMD,
};

//execute ast
void	ft_execute_ast(t_node *node);
void	ft_exec(t_node *node, int dupfd, int *cmd_index);
// exec pipe
void	ft_exec_pipe(t_pipe *node, int dupfd, int *cmd_index);
void	ft_dup2(int fd1, int fd2);
// exec cmd
void	ft_exec_cmd(t_cmd *cmd);
// exec redir
void	ft_exec_redir(t_redir *redir, int dupfd, int *cmd_index);

#endif
