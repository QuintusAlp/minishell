/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:30:31 by qalpesse          #+#    #+#             */
/*   Updated: 2024/10/07 15:55:52 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstdel(t_list *lst, void (*del)(void*))
{
	if (lst->next)
	{
		ft_lstdel(lst->next, del);
	}
	ft_lstdelone(lst, del);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (*lst)
	{
		ft_lstdel(*lst, del);
		*lst = NULL;
	}
	else
		return ;
}
