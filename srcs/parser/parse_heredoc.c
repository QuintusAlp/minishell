/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:53:05 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/19 16:56:54 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp2(char *str, char *str_to_find)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while ((str[i] && str[i] != '\n') || str_to_find[i])
	{
		if (str[i] != str_to_find[i])
			return (0);
		i++;
	}
	return (1);
}

t_list	*ft_delheredoc(t_list **token)
{
	t_list	*current;
	t_list	*new_lst;

	current = *token;
	new_lst = NULL;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			current = current->next->next;
		}
		else
		{
			ft_lstadd_back(&new_lst,
				ft_lstnew(ft_strdup(current->value), current->type));
			current = current->next;
		}
	}
	ft_lstclear(token, &free);
	return (new_lst);
}

void	ft_exit_hd(int sig)
{
	(void)sig;
	exit(1);
}

void	ft_heredoc(char *delimiter, char *file, t_env **g_env)
{
	char	*buff;
	t_trim	trim;
	char	*new_buff;
	int		fd;

	(void)g_env;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	signal(SIGINT, ft_exit_hd);
	while (1)
	{
		buff = readline("> ");
		if (buff == NULL)
			exit(0);
		init_trim(&trim);
		new_buff = process_token(buff, g_env, &trim);
		if (ft_strcmp(delimiter, new_buff) == 0)
			break ;
		ft_putstr_fd(new_buff, fd);
		ft_putstr_fd("\n", fd);
		free(buff);
	}
	if (buff)
		free (buff);
	close(fd);
}
