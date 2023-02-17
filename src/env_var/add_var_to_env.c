/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var_to_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:43:22 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/17 04:05:31 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			update_existing_var(t_env_var *env_var, char *key,
						char *value);
static t_env_var	**add_first_var(t_env_var **env_list, char *key,
						char *value);
static void			append_env_var(t_env_var *last_var, char *key, char *value);

t_env_var	**add_var_to_env(t_env_var **env_list, char *key, char *value)
{
	t_env_var	*current_var;

	if (env_list == NULL)
		return (NULL);
	else if (*env_list == NULL)
		return (add_first_var(env_list, key, value));
	current_var = *env_list;
	while (current_var != NULL)
	{
		if (update_existing_var(current_var, key, value) == SUCCESS)
			return (env_list);
		else if (current_var->next == NULL)
			break ;
		current_var = current_var->next;
	}
	append_env_var(current_var, key, value);
	return (env_list);
}

static void	append_env_var(t_env_var *last_var, char *key, char *value)
{
	t_env_var	*new_var;

	new_var = create_env_var(key, value);
	if (new_var == NULL)
	{
		ft_putstr_fd("Memory error!\n", STDERR_FILENO);
		return ;
	}
	last_var->next = new_var;
}

static t_env_var	**add_first_var(t_env_var **env_list, char *key,
										char *value)
{
	t_env_var	*new_var;

	new_var = create_env_var(key, value);
	*env_list = new_var;
	return (env_list);
}

static int	update_existing_var(t_env_var *env_var, char *key, char *value)
{
	if (ft_strncmp(key, env_var->key, ft_strlen(key) + 1) == 0)
	{
		free(env_var->value);
		env_var->value = ft_strdup(value);
		return (SUCCESS);
	}
	return (FAILURE);
}
