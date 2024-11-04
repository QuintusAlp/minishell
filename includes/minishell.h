/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:59:52 by qalpesse          #+#    #+#             */
/*   Updated: 2024/11/04 16:31:16 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

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

#endif