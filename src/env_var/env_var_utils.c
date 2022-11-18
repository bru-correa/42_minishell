/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:50:05 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/18 17:24:33 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_var	**delete_first_var(t_env_var **env_list);
static t_env_var	**delete_var(t_env_var **env_list, t_env_var *prev_var,
								t_env_var *del_var);

void	clear_env_list(t_env_var **env_list)
{
	t_env_var	*current_var;
	t_env_var	*temp_var;

	if (env_list == NULL)
		return ;
	current_var = *env_list;
	while (current_var != NULL)
	{
		temp_var = current_var;
		current_var = current_var->next;
		free(temp_var->key);
		free(temp_var->value);
		free(temp_var);
	}
	free(env_list);
}

t_env_var	**delete_env_var(t_env_var **env_list, char *key)
{
	t_env_var	*current_var;

	if (env_list == NULL)
		return (NULL);
	else if (*env_list == NULL)
		return (env_list);
	if (ft_strncmp((*env_list)->key, key, ft_strlen(key) + 1) == 0)
		return (delete_first_var(env_list));
	current_var = *env_list;
	while (current_var->next != NULL)
	{
		if (ft_strncmp(current_var->next->key, key, ft_strlen(key) + 1) == 0)
			return (delete_var(env_list, current_var, current_var->next));
		current_var = current_var->next;
	}
	return (env_list);
}

static t_env_var	**delete_first_var(t_env_var **env_list)
{
	t_env_var	*first_var;

	first_var = *env_list;
	*env_list = (*env_list)->next;
	free(first_var->key);
	free(first_var->value);
	free(first_var);
	return (env_list);
}

static t_env_var	**delete_var(t_env_var **env_list, t_env_var *prev_var,
								t_env_var *del_var)
{
	prev_var->next = del_var->next;
	free(del_var->key);
	free(del_var->value);
	free(del_var);
	return (env_list);
}
