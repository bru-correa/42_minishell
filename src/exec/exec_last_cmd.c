/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_last_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:28:31 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/09 13:55:48 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_exit_status(t_cmd *cmd, int status);

void	exec_last_cmd(t_cmd *cmd, t_pipeline *pipeline, t_env_var **env_list)
{
	int	pid;
	int	status;

	if (cmd->args == NULL)
		return ;
	pid = fork();
	if (pid == CHILD_ID)
	{
		if (is_builtin(cmd->args[0]))
			exec_builtin(cmd, env_list, pipeline);
		else
			exec_cmd(cmd, env_list, pipeline);
	}
	waitpid(pid, &status, 0);
	set_exit_status(cmd, status);
}

// Only need to set the exit status when the last command is not a builtin
static void	set_exit_status(t_cmd *cmd, int status)
{
	if (WIFEXITED(status))
	{
		if (is_builtin(cmd->args[0]) == FALSE)
			g_exit_status = WEXITSTATUS(status);
	}
}
