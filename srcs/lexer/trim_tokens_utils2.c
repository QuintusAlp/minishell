/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_tokens_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:26:04 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/21 19:35:19 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_singles(char *str, t_trim *trim)
{
	char	*tmp;

	trim->k = 1;
	while (str[trim->k] != '\'')
		trim->k++;
	tmp = ft_strndup(&str[1], (trim->k - 1));
	add_to_newstr(tmp, trim);
	trim->i += ft_strlen(tmp) + 2;
}

void	init_trim(t_trim *trim)
{
	trim->j = 0;
	trim->i = 0;
	trim->k = 0;
	trim->new_str = ft_strdup("");
	trim->temp = ft_strdup("");
}
