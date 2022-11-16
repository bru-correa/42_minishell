/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:43:22 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/16 12:52:37 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_existing_var(t_env_var *env_var, char *key, char *value);

t_env_var	**create_env_vars_list(void)
{
	t_env_var	**env_vars;

	env_vars = malloc(sizeof(t_env_var*));
	if (env_vars == NULL)
		return (NULL);
	*env_vars = NULL;
	return (env_vars);
}

t_env_var	*create_env_var(char *key, char *value)
{
	t_env_var	*env_var;

	env_var = malloc(sizeof(t_env_var));
	if (env_var == NULL)
		return (NULL);
	env_var->key = key;
	env_var->value = value;
	return (env_var);
}

// Add or update if already exists
t_env_var	**env_var_add(t_env_var **env_vars, char *key, char *value)
{
	t_env_var	*current_var;
	t_env_var	*new_var;

	if (env_vars == NULL)
		return (NULL);
	current_var = *env_vars;
	while (current_var != NULL)
	{
		if (update_existing_var(current_var, key, value) == SUCCESS)
			return (env_vars);
		else if (current_var->next == NULL)
			break ;
		current_var = current_var->next;
	}
	new_var = create_env_var(key, value);
	if (new_var == NULL)
	{
		ft_putstr_fd("Memory error!\n", STDERR_FILENO);
		return (env_vars);
	}
	current_var->next = new_var;
	return (env_vars);
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
