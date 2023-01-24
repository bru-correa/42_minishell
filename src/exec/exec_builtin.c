/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:03:26 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/23 20:59:10 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_cmd_valid(t_cmd *cmd);

void	exec_builtin(t_cmd *cmd, t_env_var **env_list, t_pipeline *pipeline)
{
	if (is_cmd_valid(cmd) == FALSE)
		return ;
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		repl_exit(pipeline, env_list);
}

static int	is_cmd_valid(t_cmd *cmd)
{
	if (cmd == NULL)
		return (FALSE);
	else if (cmd->args[0] == NULL)
		return (FALSE);
	return (TRUE);
}
