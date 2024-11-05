/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:56:12 by marlonco          #+#    #+#             */
/*   Updated: 2024/10/07 16:07:35 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_split
{
	int		i;
	int		j;
	int		k;
	char	**str;
}	t_split;

static void	ft_free(char **array, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static int	ft_count(char const *s, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			k++;
		i++;
	}
	return (k);
}

static char	**ft_array_malloc(char const *s, char c, t_split st)
{
	st.str = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!st.str)
		return (0);
	while (s[st.i])
	{
		if (s[st.i] != c && s[st.i] != '\0')
		{
			st.j = 0;
			while (s[st.i + st.j] != c && s[st.i + st.j] != '\0')
				st.j++;
			st.str[st.k] = malloc(sizeof(char) * (st.j + 1));
			if (st.str[st.k] == NULL)
			{
				ft_free(st.str, st.k);
				return (NULL);
			}
			st.k++;
			st.i += st.j - 1;
		}
		st.i++;
	}
	st.str[st.k] = NULL;
	return (st.str);
}

static void	ft_fill_array_str(char const *s, char c, char **array)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c && s[i] != '\0')
		{
			j = 0;
			while (s[i + j] != c && s[i + j] != '\0')
			{
				array[k][j] = s[i + j];
				j++;
			}
			array[k][j] = '\0';
			i += j - 1;
			k++;
		}
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	t_split	st;

	if (s == NULL)
		return (NULL);
	st.i = 0;
	st.j = 0;
	st.k = 0;
	array = ft_array_malloc(s, c, st);
	if (array == NULL)
		return (NULL);
	ft_fill_array_str(s, c, array);
	return (array);
}

typedef struct s_env {
	char			*name;
	char			*value;
	int				index;
	struct s_env	*next;
}	t_env;

// fct to init wih the initial en
void	init_env()
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


// fct to update the index after one env has been deleted 
void	update_index(t_env *env, int deleted_index)
{
	t_env	*current;
	
	current = env;
	while (current)
	{
		if (current->index > deleted_index)
			current->index -= 1;
		current = current->next;	
	}
}

// HAVE TO TEST IT 

int main()
{
	t_env 	*env;
	init_env();
	while (env)
	{
		printf("%s %s %d\n", env->name, env->value, env->index);
		env = env->next;
	}
}