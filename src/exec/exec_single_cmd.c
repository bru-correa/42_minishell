/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:21:16 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/26 11:56:30 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

/* TODO: exec_single_cmd
 * Exec single cmd will handle redirections (it won't deal with pipes),
 * and then, it checks if the cmd is a builtin or not.
 * If it is, execute and get the return status from the builtin,
 * and set  g_exit_status. If itsn't, fork and exec the cmd,
 * and set the g_exit_status after the execution.
*/

// WIFEXITED return true if the child process terminated normally
void	exec_single_cmd(t_cmd *cmd, t_env_var **env_list, t_pipeline *pipeline)
{
	int	std_fd[2];
	int	pid;
	int	status;

	backup_std_fd(std_fd);
	if (redirect_list(cmd->rdir_list) == ERROR)
		return;
	if (is_builtin(cmd->args[0]) == TRUE)
	{
		exec_builtin(cmd, env_list, pipeline);
		return ;
	}
	pid = fork();
	if (pid == CHILD_ID)
	{
		exec_cmd(cmd, env_list, pipeline);
		clear_env_list(env_list);
		clear_pipeline(pipeline);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, WNOHANG);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	restore_std_fd(std_fd);
}
