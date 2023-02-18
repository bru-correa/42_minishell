/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:07:42 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/18 01:23:06 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_cmd *cmd, t_env_var **env_list)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		delete_env_var(env_list, cmd->args[i]);
		i++;
	}
	return (0);
}
