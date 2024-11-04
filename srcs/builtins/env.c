/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:22:35 by marlonco          #+#    #+#             */
/*   Updated: 2024/11/04 16:26:10 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	env displays a list of all environmental variables of the sessions and their current values 
		-> getenv(const char *name) with name = a given environmental variable 
			--> to retrieve the value of a variable with its name , returns a char *
*/

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