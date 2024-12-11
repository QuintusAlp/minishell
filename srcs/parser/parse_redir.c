/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:26:20 by qalpesse          #+#    #+#             */
/*   Updated: 2024/12/11 14:54:16 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void    handle_signals_bis(void);
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

int ft_cmdlen(char *str)
{
	int	i;

	i = 0;
	str = str + 2;
	while (str[i] != ')')
		i++;
	return (i);
}

t_list	*ft_delheredoc(t_list **token)
{
	t_list *current;
	t_list *new_lst;

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
			ft_lstadd_back(&new_lst, ft_lstnew(ft_strdup(current->value), current->type));
			current = current->next;
		}
	}
	ft_lstclear(token, &free);
	return (new_lst);
}

void ft_exit_hd(int sig)
{
	(void)sig;
	exit(1);
}
void	ft_heredoc(char *delimiter, char *file, t_env **g_env)
{
	char *buff;
	int	fd;
	(void)g_env;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	signal(SIGINT, ft_exit_hd);
	while(1)
	{
		buff = readline("> ");
		if (buff == NULL)
			exit(0);
		if (ft_strcmp(delimiter, buff) == 0)
			break;
		ft_putstr_fd(buff, fd);	
		ft_putstr_fd("\n", fd);	
		free(buff);
	}
	if (buff)
		free (buff);
	close(fd);
}

t_node	*ft_redirnode(char *file, t_node *cmd, int type, t_list **token)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	redir->type = type;
	redir->cmd = cmd;
	redir->file = file;
	ft_lstclear(token, &free);
	return ((t_node *)redir);
}

int ft_token_isredir(t_list *token)
{
	if (!token)
		return (0);
	if (token->type == I_REDIR || token->type == HEREDOC)
		return (1);
	if (token->type == O_REDIR_APPEND || token->type == O_REDIR_TRUNC)
		return (1);
	return (0);
}

int	ft_check_other_redir(t_list *token)
{
	t_list 		*tokens = token->next;
	while (tokens)
	{
		if (ft_token_isredir(tokens))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

t_list	*ft_get_prevredir(t_list *token)
{
	t_list	*prev;

	prev = NULL;
	while (!ft_token_isredir(token))
	{
		ft_lstadd_back(&prev, ft_lstnew(ft_strdup(token->value), token->type));
		token = token->next;
	}
	token = token->next;
	if (token && token-> type == WORD)
		token = token->next;
	while(token)
	{
		ft_lstadd_back(&prev, ft_lstnew(ft_strdup(token->value), token->type));
		token = token->next;
	}
	return (prev);
}

char *ft_get_file_and_type(t_list *token, int *type, int *hd_index, t_env **g_env)
{
	t_list *start_lst;
	char *hd_file;
	char *index;

	start_lst = token;
	(void) start_lst; // MODIF TO COMPILE 
	while (!ft_token_isredir(token))
		token = token->next;
	*type = token->type;
	token = token->next;
	if (token)
	{
		if (*type == HEREDOC)
		{
			index = ft_itoa(*hd_index);
			hd_file = ft_strjoin("/tmp/hd_file", index);
			free(index);
			(*hd_index) --;
			ft_set_sig(2);
			int pid = fork();
			if (pid == 0)
			{
				ft_heredoc(token->value, hd_file, g_env);
				exit(0);
			}
			ft_stats(pid);
			return (hd_file);
		}
		else
			return (ft_strdup(token->value));
	}
	else
		return (ft_strdup("\n"));
}
