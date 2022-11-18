/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_with_envp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:03:48 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/18 17:17:34 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_key(char *env);
static int	get_key_size(char *env);
static char	*get_value(char *env);

t_env_var	**create_env_with_envp(char **envp)
{
	int			i;
	t_env_var	**env_list;
	char		*key;
	char		*value;

	if (envp == NULL)
		return (NULL);
	i = 0;
	env_list = create_env_list();
	if (env_list == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		env_list = add_var_to_env(env_list, key, value);
		i++;
	}
	return (env_list);
}

static char	*get_key(char *env)
{
	char	*key;
	int		size;

	size = get_key_size(env);
	key = ft_substr(env, 0, size);
	return (key);
}

static int	get_key_size(char *env)
{
	int	i;

	i = 0;
	while (env[i] != '=')
		i++;
	return (i);
}

static char	*get_value(char *env)
{
	char	*value;

	value = ft_strchr(env, '=') + 1;
	value = ft_substr(env, 0, ft_strlen(value));
	return (value);
}