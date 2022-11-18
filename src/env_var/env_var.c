/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:43:22 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/18 17:15:56 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			update_existing_var(t_env_var *env_var, char *key,
										char *value);
static t_env_var	**add_first_var(t_env_var **env_list, char *key,
									char *value);

t_env_var	**create_env_list(void)
{
	t_env_var	**env_list;

	env_list = malloc(sizeof(t_env_var*));
	if (env_list == NULL)
		return (NULL);
	*env_list = NULL;
	return (env_list);
}

t_env_var	*create_env_var(char *key, char *value)
{
	t_env_var	*env_var;

	env_var = malloc(sizeof(t_env_var));
	if (env_var == NULL)
		return (NULL);
	env_var->key = key;
	env_var->value = value;
	env_var->next = NULL;
	return (env_var);
}

// Add or update if already exists
t_env_var	**add_var_to_env(t_env_var **env_list, char *key, char *value)
{
	t_env_var	*current_var;
	t_env_var	*new_var;

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
	new_var = create_env_var(key, value);
	if (new_var == NULL)
	{
		ft_putstr_fd("Memory error!\n", STDERR_FILENO);
		return (env_list);
	}
	current_var->next = new_var;
	return (env_list);
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
		env_var->value = value;
		return (SUCCESS);
	}
	return (FAILURE);
}
