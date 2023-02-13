/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:08:42 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/13 00:23:52 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_new_pipe(int prev_pipe);
static void	exec_in_child(t_cmd *cmd, t_pipeline *pipeline,
							t_env_var **env_list, int pipe_in);
static void	rdir_last_pipe(int pipe_in, t_pipeline *pipeline);

void	exec_pipeline(t_pipeline *pipeline, t_env_var **env_list)
{
	int		i;
	int		pipe_in;
	t_cmd	*cmd;

	pipe_in = STDIN_FILENO;
	i = 0;
	cmd = pipeline->cmds[i];
	while (i < pipeline->cmd_count - 1)
	{
		pipe_in = open_new_pipe(pipe_in);
		if (redirect_list(cmd->rdir_list, pipeline, env_list) == 0)
			exec_in_child(cmd, pipeline, env_list, pipe_in);
		i++;
		cmd = pipeline->cmds[i];
	}
	rdir_last_pipe(pipe_in, pipeline);
	if (redirect_list(cmd->rdir_list, pipeline, env_list) == 0)
		exec_last_cmd(cmd, pipeline, env_list);
}

static int	open_new_pipe(int prev_pipe)
{
	int	pipe_fd[2];

	if (prev_pipe != STDIN_FILENO)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	pipe(pipe_fd);
	dup2(pipe_fd[OUT], STDOUT_FILENO);
	close(pipe_fd[OUT]);
	return (pipe_fd[IN]);
}

// WARNING: Provisory function clean_process()
static void	exec_in_child(t_cmd *cmd, t_pipeline *pipeline,
							t_env_var **env_list, int pipe_in)
{
	int	pid;

	if (cmd->args == NULL)
		return ;
	pid = fork();
	sig_setup_exec(pid);
	if (pid == CHILD_ID)
	{
		close(pipe_in);
		clean_process();
		if (is_builtin(cmd->args[0]))
			exec_builtin(cmd, env_list, pipeline);
		else
			exec_cmd(cmd, env_list, pipeline);
	}
}

static void	rdir_last_pipe(int pipe_in, t_pipeline *pipeline)
{
	dup2(pipe_in, STDIN_FILENO);
	close(pipe_in);
	dup2(pipeline->std_fd[OUT], STDOUT_FILENO);
}
