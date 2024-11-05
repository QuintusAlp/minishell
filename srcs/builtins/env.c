/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:22:35 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/05 15:06:01 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	env displays a list of all environmental variables of the sessions and their current values 
		-> getenv(const char *name) with name = a given environmental variable 
			--> to retrieve the value of a variable with its name , returns a char *
*/

void	init_envv()
{
	t_env	*env;
	t_env	*current;
	t_env	*new_node;
	extern char	**environ;
	int			i;
	char		**result;

	i = 0;
	env = NULL;
	current = NULL;
	while (environ[i] != NULL)
	{
		new_node = (t_env *)malloc(sizeof(t_env));
		if (!new_node)
			return;
			//error("Malloc error\n");
		result = ft_split(environ[i], '=');
		new_node->index = i;
		new_node->name = result[0]; 
		new_node->value = result[1];
		new_node->next = NULL;
		if (!env)
			env = new_node;
		else 
			current->next = new_node;
		current = new_node;
		i++;
	}
}

void	env(void)
{
	extern char	**environ;
	int i;

	i = 0;
	if (!(environ) || !(*environ))
		return;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
// int main()
// {
// 	env();
// }