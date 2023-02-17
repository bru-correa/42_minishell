/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:28:04 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/16 23:45:39 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	get_env_count(t_env_var **env_list);
static void	set_env_vars(char **env, t_env_var **env_list);
static char	*get_var(t_env_var *env_item);

char	**get_env_array(t_env_var **env_list)
{
	char	**env;
	int		length;

	if (env_list == NULL)
		return (NULL);
	length = get_env_count(env_list);
	env = malloc(sizeof(char *) * (length + 1));
	if (env == NULL)
		return (NULL);
	set_env_vars(env, env_list);
	return (env);
}

static int	get_env_count(t_env_var **env_list)
{
	int			count;
	t_env_var	*current;

	current = *env_list;
	count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static void	set_env_vars(char **env, t_env_var **env_list)
{
	int			i;
	t_env_var	*current;

	i = 0;
	current = *env_list;
	while (current != NULL)
	{
		env[i] = get_var(current);
		i++;
		current = current->next;
	}
	env[i] = NULL;
}

static char	*get_var(t_env_var *env_item)
{
	char	*key;
	char	*var;

	key = ft_strjoin(env_item->key, "=");
	var = ft_strjoin(key, env_item->value);
	free(key);
	return (var);
}
