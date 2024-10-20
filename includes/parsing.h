/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:41:47 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/07 10:12:08 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
enum e_char_token
{
	PIPE,
	WORD,
	I_REDIR,
	O_REDIR_APPEND,
	O_REDIR_TRUNC,
	HEREDOC,
	CMD
};

typedef struct	s_node
{
	int	type;
}	t_node;

 typedef struct s_cmd	
{
	int		type;
	char 	**argv;
	char 	**env;
}	t_cmd;

 typedef struct s_redir 
{
	int		type;
	t_node	*cmd;
	char	*file;
}	t_redir;

 typedef struct s_pipe
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_pipe;
#endif
