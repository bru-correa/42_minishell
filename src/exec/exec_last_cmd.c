/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_last_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:28:31 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/13 00:48:39 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_exit_status(int status);

// WARNING: Provisory function clean_process()
void	exec_last_cmd(t_cmd *cmd, t_pipeline *pipeline, t_env_var **env_list)
{
	int	pid;
	int	status;

	status = 0;
	if (cmd->args == NULL)
		return ;
	pid = fork();
	sig_setup_exec(pid);
	if (pid == CHILD_ID)
	{
		clean_process();
		if (is_builtin(cmd->args[0]))
			exec_builtin(cmd, env_list, pipeline);
		else
			exec_cmd(cmd, env_list, pipeline);
	}
	waitpid(pid, &status, 0);
	set_exit_status(status);
}

// Only need to set the exit status when the last command is not a builtin
static void	set_exit_status(int status)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		ft_printf("\n");
		g_exit_status = status + 128;
	}
}
