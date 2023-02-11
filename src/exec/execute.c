/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:19:13 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/10 11:51:04 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* NOTE: exec_single_cmd
 * Exec single cmd will handle redirections (it won't deal with pipes),
 * and then, it checks if the cmd is a builtin or not.
 * If it is, execute and get the return status from the builtin,
 * and set  g_exit_status. If itsn't, fork and exec the cmd,
 * and set the g_exit_status after the execution.
*/

/* NOTE: exec_pipeline
 * Exec pipeline handle redirections and deal with all the pipes. It checks
 * if the cmd is a builtin or not.
 * If it is, execute and get the return status from the builtin,
 * and set  g_exit_status. If itsn't, fork and exec the cmd,
 * and set the g_exit_status after the execution.
*/

void	execute(t_pipeline *pipeline, t_env_var **env_list)
{
	t_cmd	*first_cmd;

	backup_std_fd(pipeline->std_fd);
	if (pipeline->cmds == NULL)
		return ;
	first_cmd = pipeline->cmds[0];
	if (pipeline->cmd_count == 1)
		exec_single_cmd(first_cmd, env_list, pipeline);
	else
		exec_pipeline(pipeline, env_list);
	restore_std_fd(pipeline->std_fd);
}
