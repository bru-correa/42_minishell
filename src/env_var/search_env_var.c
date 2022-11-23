/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:44:04 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/23 15:53:36 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_env_var(t_env_var **env_list, char *key)
{
	t_env_var	*current_var;
	size_t		key_length;
	char		*var_value;

	if (env_list == NULL)
		return (NULL);
	key_length = ft_strlen(key);
	current_var = *env_list;
	while (current_var != NULL)
	{
		if (ft_strncmp(current_var->key, key, key_length + 1) == 0)
		{
			var_value = ft_strdup(current_var->value);
			return (var_value);
		}
		current_var = current_var->next;
	}
	return (ft_strdup(""));
}
