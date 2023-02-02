/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:17:32 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/01 21:22:12 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// WARNING: Provisory function
int	env(t_env_var **env_list)
{
	t_env_var	*current_var;

	if (env_list == NULL)
		return (1);
	current_var = *env_list;
	while (current_var != NULL)
	{
		ft_printf("%s=", current_var->key);
		ft_printf("%s\n", current_var->value);
		current_var = current_var->next;
	}
	return (0);
}
