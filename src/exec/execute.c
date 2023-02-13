/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:19:13 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/13 03:43:59 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_pipeline *pipeline, t_env_var **env_list)
{
	t_cmd	*first_cmd;

	backup_default_fd(pipeline->default_fd);
	if (pipeline->cmds == NULL)
		return ;
	first_cmd = pipeline->cmds[0];
	if (pipeline->cmd_count == 1)
		exec_single_cmd(first_cmd, env_list, pipeline);
	else
		exec_pipeline(pipeline, env_list);
	restore_default_fd(pipeline->default_fd);
}
