/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:41:47 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/24 08:42:48 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <stdbool.h>

enum				e_char_token
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
// env
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;
//--
typedef struct s_node
{
	int				type;
}					t_node;

typedef struct s_cmd
{
	int				type;
	char			**argv;
	t_env			**g_env;
}					t_cmd;

typedef struct s_redir
{
	int				type;
	t_node			*cmd;
	char			*file;
}					t_redir;

typedef struct s_pipe
{
	int				type;
	t_node			*left;
	t_node			*right;
}					t_pipe;

typedef struct s_trim
{
	bool			in_single;
	bool			in_double;
	int				c;
	int				end_index;
	int				i;
	int				j;
	int				k;
	int				flag;
	char			*new_str;
	char			*temp;
}					t_trim;

// GLOBAL VAR
int					g_exitcode;
#endif