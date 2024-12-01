/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:22:35 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/29 16:04:08 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	env displays a list of all environmental variables of the sessions and their current values 
		-> getenv(const char *name) with name = a given environmental variable 
			--> to retrieve the value of a variable with its name , returns a char *
*/

// t_env	*remaining_env(t_env **env)
// {
// 	char 	**pwd_export;
// 	char	*pwd;
// 	char	**export_;
// 	char	**shlvl_export;

// 	pwd_export[0] = NULL;
// 	export_[0] = NULL;
// 	shlvl_export[0] = NULL;
	
// 	pwd = getcwd(NULL, 0);
// 	if (!pwd)
// 		return (NULL);
// 	pwd_export[1] = malloc((5 + ft_strlen(pwd)) * sizeof(char));
// 	if (!pwd_export)
// 		return (NULL);
// 	pwd_export[1] = ft_strjoin("PWD=", pwd);
// 	export_[1] = malloc((ft_strlen(pwd_export) + 13) * sizeof(char));
// 	if(!export_)
// 		return (NULL);
// 	export_[1] = ft_strjoin("_=", pwd_export[1]);
// 	export_[1] = ft_strjoin(export_[1], "/minishell");
// 	shlvl_export[1] = malloc(8 * sizeof(char));
// 	if (!shlvl_export)
// 		return (NULL);
// 	shlvl_export[1] = "SHLVL=1";
// 	export(pwd_export, &env); // how to refer to env ?
// 	export(shlvl_export, &env);
// 	export(export_, &env);
// 	return (env);
// }

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
	// if (environ == NULL)
	// 	remaining_env(env);
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