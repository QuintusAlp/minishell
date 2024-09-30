/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:56:12 by marlonco          #+#    #+#             */
/*   Updated: 2024/09/30 15:30:18 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_env {
	char			*name;
	char			*value;
	int				index;
	struct s_env	*next;
}	t_env;

// fct to init wih the initial en
void	init_env()
{
	t_env	env;
	extern char	**environ;
	int			i;
	char		**result;

	i = 0;
	while (environ[i] != NULL)
	{
		result = ft_split(environ[i], '=');
		env.index = i;
		env.name = result[0]; 
		env.value = result[1];
		i++;
		env = env.next;
	}
}


// fct to update the index after one env has been deleted 
void	update_index(t_env env)
{
	int i;

	i = env.index;
	while (env.next)
	{
		env.next->index = i;
		i++;
		env = env.next;	
	}
}