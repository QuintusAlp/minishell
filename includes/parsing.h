/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:41:47 by qalpesse          #+#    #+#             */
/*   Updated: 2024/09/24 15:12:56 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

enum e_char_token
{
	LITTERAL,
	PIPE,
	AND,
	OR,
	REDIR,
	S_QUOTE,
	D_QUOTE,
	WORD
};


#endif
