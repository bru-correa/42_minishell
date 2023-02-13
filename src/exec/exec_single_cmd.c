/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:21:16 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/12 14:41:16 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static void	exec_in_child(t_cmd *cmd, t_env_var **env_list,
			t_pipeline *pipeline);

void	exec_single_cmd(t_cmd *cmd, t_env_var **env_list, t_pipeline *pipeline)
{
	if (redirect_list(cmd->rdir_list, pipeline, env_list) == ERROR)
		return;
	if (cmd->args == NULL)
		return ;
	else if (is_builtin(cmd->args[0]) == TRUE)
		exec_builtin(cmd, env_list, pipeline);
	else
		exec_in_child(cmd, env_list, pipeline);
}

// WIFEXITED return true if the child process terminated normally
static void	exec_in_child(t_cmd *cmd, t_env_var **env_list,
			t_pipeline *pipeline)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	sig_setup_exec(pid);
	if (pid == CHILD_ID)
	{
		exec_cmd(cmd, env_list, pipeline);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		ft_printf("\n");
		g_exit_status = status + 128;
	}
}
