/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:22:35 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/28 20:25:11 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	env displays a list of all environmental variables of the sessions and their current values 
		-> getenv(const char *name) with name = a given environmental variable 
			--> to retrieve the value of a variable with its name , returns a char *
*/

void	remaining_env()
{
	char *pwd_export;

	pwd_export = malloc((5 + ft_strlen(pwd)) * sizeof(char));
	if (!pwd_export)
		return (NULL);
	pwd_export = ft_strjoin("PWD=", getcwd(NULL, 0));
	export(pwd_export, ); // how to refer to env ?
	export("SHLVL=1");
	export("_="); // HOW TO REFER TO THE SHELL BINARY 
}

t_env *init_envv()
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
	if (environ == NULL)
		remaining_envv();
	while (environ[i] != NULL)
	{
		new_node = (t_env *)malloc(sizeof(t_env));
		if (!new_node)
			return(error("Malloc error\n"), NULL);
		result = ft_split(environ[i], '=');
		if (!result)
			return(free(new_node), NULL);
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
	return (env);
}

//CHECK THE WORKING OF ENVV
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
// 	t_env *env = init_envv
// }