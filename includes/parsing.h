/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:41:47 by qalpesse          #+#    #+#             */
/*   Updated: 2024/11/11 11:59:31 by marlonco         ###   ########.fr       */
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
	REDIR,
	CMD,
};

typedef struct	s_node
{
	int	type;
}	t_node;

typedef struct s_env {
	char			*name;
	char			*value;
	int				index;
	struct s_env	*next;
}	t_env;

 typedef struct s_cmd	
{
	int		type;
	char 	**argv;
	t_env 	**env;
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