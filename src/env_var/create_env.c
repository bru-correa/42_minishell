/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:16:44 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/18 18:22:23 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	**create_env_list(void)
{
	t_env_var	**env_list;

	env_list = malloc(sizeof(t_env_var *));
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
