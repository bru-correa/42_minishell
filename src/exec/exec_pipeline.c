/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 10:02:22 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/19 12:27:43 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

/* TODO: exec_pipeline
 * Exec pipeline handle redirections and deal with all the pipes. It checks
 * if the cmd is a builtin or not.
 * If it is, execute and get the return status from the builtin,
 * and set  g_exit_status. If itsn't, fork and exec the cmd,
 * and set the g_exit_status after the execution.
*/

static void	rdir_prev_pipe(int *pipe_in);
static void	create_new_pipe(int *pipe_in);
static int	is_last_cmd(int cmd_index, int cmd_count);

// TODO: Fork is in exec_cmd but needs to be in here
void	exec_pipeline(t_pipeline *pipeline, t_env_var **env_list)
{
	int	i;
	int	pipe_in;
	int	std_fd[2];

	backup_std_fd(std_fd);
	pipe_in = 0;
	i = 0;
	while (is_last_cmd(i, pipeline->cmd_count) == FALSE)
	{
		rdir_prev_pipe(&pipe_in);
		create_new_pipe(&pipe_in);
		redirect_list(pipeline->cmds[i]->rdir_list);
		exec_cmd(pipeline->cmds[i], env_list, pipeline);
		i++;
	}
	rdir_prev_pipe(&pipe_in);
	dup2(std_fd[OUT], STDOUT_FILENO);
	redirect_list(pipeline->cmds[i]->rdir_list);
	exec_cmd(pipeline->cmds[i], env_list, pipeline);
	restore_std_fd(std_fd);
}

static void	rdir_prev_pipe(int *prev_pipe_in)
{
	dup2(*prev_pipe_in, STDIN_FILENO);
	if (prev_pipe_in != 0)
		close(*prev_pipe_in);
}

static void	create_new_pipe(int *pipe_in)
{
	int	new_pipe[2];

	if (pipe(new_pipe) == -1)
		return;
	*pipe_in = dup(new_pipe[IN]);
	dup2(new_pipe[OUT], STDOUT_FILENO);
	close(new_pipe[IN]);
	close(new_pipe[OUT]);
}

static int	is_last_cmd(int cmd_index, int cmd_count)
{
	if (cmd_index == cmd_count - 1)
		return (TRUE);
	else
		return (FALSE);
}
