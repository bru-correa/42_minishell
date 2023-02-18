/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:04:01 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/18 00:34:46 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_var(t_env_var *env_var);

void	print_export(t_env_var **env_list)
{
	t_env_var	*env_var;

	env_var = *env_list;
	while (env_var != NULL)
	{
		print_var(env_var);
		env_var = env_var->next;
	}
}

static void	print_var(t_env_var *env_var)
{
	ft_printf("declare -x ");
	ft_printf("%s=\"%s\"\n", env_var->key, env_var->value);
}
