/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:19:13 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/28 12:45:09 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TODO:
 * If the cmd_count == 1, call exec_single_cmd, else, call exec_pipeline.
*/

/* TODO: exec_single_cmd
 * Exec single cmd will handle redirections (it won't deal with pipes),
 * and then, it checks if the cmd is a builtin or not.
 * If it is, execute and get the return status from the builtin,
 * and set  g_exit_status. If itsn't, fork and exec the cmd,
 * and set the g_exit_status after the execution.
*/

/* TODO: exec_pipeline
 * Exec pipeline handle redirections and deal with all the pipes. It checks
 * if the cmd is a builtin or not.
 * If it is, execute and get the return status from the builtin,
 * and set  g_exit_status. If itsn't, fork and exec the cmd,
 * and set the g_exit_status after the execution.
*/

/* WARNING: builtin
 * Every builtin MUST return an int with the exit status
*/

// WARNING: THE FORK MUST BE OUT OF EXEC_CMD, EXEC_BUILTIN.
// EXEC_PIPELINE AND EXEC_SINGLE_CMD MUST BE THE RESPONSIBLES FOR THIS!!!!

/*
 * NOTE: The g_exit_code can be set after command exit,
 * or manually after a single builtin
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
