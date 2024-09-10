/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:18:49 by qalpesse          #+#    #+#             */
/*   Updated: 2024/05/14 09:44:56 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*lst_dup;

	if (lst)
	{
		size = 1;
		lst_dup = lst;
	}
	else
		return (0);
	while (lst_dup->next)
	{
		size++;
		lst_dup = lst_dup->next;
	}
	return (size);
}
/*
void ft_printlst(t_list **lst)
{
	t_list *tmp = *lst;
	while(tmp != NULL) 
	{
		printf("%s ", (char*)tmp->content); 
		tmp = tmp->next; 
	} 
}
int	main(void)
{
	t_list *element_3 = ft_lstnew("c");
	t_list *element_2 = ft_lstnew("b");
	element_2->next = element_3;
	t_list *element_1 = ft_lstnew("a");
	element_1->next = element_2;
	ft_lstadd_front(&element_1, ft_lstnew("z"));
	ft_printlst(&element_1);
	printf("\n %d", ft_lstsize(element_1));
}
*/