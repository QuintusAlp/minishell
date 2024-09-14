/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:38:19 by qalpesse          #+#    #+#             */
/*   Updated: 2024/08/07 17:14:46 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# ifdef BUFFER_SIZE
#  if BUFFER_SIZE > 2147483646
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 2147483645
#  endif
# endif
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>

char	*get_next_line(int fd);
//utils
char	*ft_strjoin_bis(char *s1, char *s2);
int		ft_findchar_bis(char c, char *str);
#endif