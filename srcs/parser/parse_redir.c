/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:26:20 by qalpesse          #+#    #+#             */
/*   Updated: 2024/11/03 16:41:23 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(char *str, char *str_to_find)
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
void ft_exec_hd_cmd(char *prompt, char **env)
{
	t_list *tokens;
	t_node *ast;
	int		nbr_heredoc;
	int		nbr_heredoc_bis;

	if (!prompt)
		return ;
	tokens = NULL;
	ast = NULL;
	ft_lexer(prompt, &tokens);
	tokens = ft_delheredoc(&tokens);
	//ft_printlst(tokens);
	nbr_heredoc = ft_countheredocs(tokens);
	nbr_heredoc_bis = nbr_heredoc;
	ast = ft_parsetoken(&tokens, env, &nbr_heredoc);
	//ast_printer(ast, 0);
	ft_execute_ast(ast);
	ft_free_ast(ast);
	ft_del_hdfiles(nbr_heredoc_bis);
	//system("leaks minishell");
	return ;
}
void	ft_write_hdline(char *str, char **env, char *file)
{
	char	*buff;
	int		pid;
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_error("open");
	while (*str)
	{
		if (*str == '$' && *(str + 1) == '(' && ft_strchr(str, ')'))
		{
			buff = malloc(ft_cmdlen(str) + 1);
			ft_strlcpy(buff, (str + 2), ft_cmdlen(str) + 1);
			pid = fork();
			if (pid == -1)
				ft_error("fork error");
			if (pid == 0)
			{
				if (dup2(fd, 1) == -1)
					ft_error("dup2");
				if (dup2(fd, 2) == -1)
					ft_error("dup2");
				close(fd);
				int fd2 = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (dup2(fd2, 0) == -1)
					ft_error("dup2");
				close(fd2);
				ft_exec_hd_cmd(buff, env);
				free(buff);
				exit(0);
			}
			else
			{
				waitpid(pid, NULL, 0);
			}
			str += ft_cmdlen(str) + 3;
			free(buff);
		}
		else
		{
			write(fd, str, 1);
			if (*(str + 1) == '\0')
				write(fd, "\n", 1);
			str++;
		}
	}
	close(fd);
}
void	ft_heredoc(char *delimiter, char *file, char **env)
{
	char *buff;
	int	fd;
		
	buff = readline("> ");
	if (ft_strcmp(buff, delimiter))
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		close (fd);
	}
	while (!ft_strcmp(buff, delimiter))
	{
		ft_write_hdline(buff, env, file);
		free(buff);
		buff = readline("> ");
	}
	free (buff);
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

char *ft_get_file_and_type(t_list *token, int *type, int *hd_index, char **env)
{
	t_list *start_lst;
	char *hd_file;
	char *index;

	start_lst = token;
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
			ft_heredoc(token->value, hd_file, env);
			return (hd_file);
		}
		else
			return (ft_strdup(token->value));
	}
	else
		return (ft_strdup("\n"));
}

