/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:08:42 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/01 11:25:42 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_new_pipe(int prev_pipe);
static void	exec_in_child(t_cmd *cmd, t_pipeline *pipeline,
							t_env_var **env_list);
static void	rdir_last_pipe(int pipe_in, t_pipeline *pipeline);

void	exec_pipeline(t_pipeline *pipeline, t_env_var **env_list)
{
	int	i;
	int	pipe_in;

	pipe_in = dup(STDIN_FILENO);
	i = 0;
	while (i < pipeline->cmd_count - 1)
	{
		pipe_in = open_new_pipe(pipe_in);
		redirect_list(pipeline->cmds[i]->rdir_list, pipeline, env_list);
		exec_in_child(pipeline->cmds[i], pipeline, env_list);
		i++;
	}
	rdir_last_pipe(pipe_in, pipeline);
	redirect_list(pipeline->cmds[i]->rdir_list, pipeline, env_list);
	exec_last_cmd(pipeline->cmds[i], pipeline, env_list);
}

static int	open_new_pipe(int prev_pipe)
{
	int	pipe_fd[2];

	dup2(prev_pipe, STDIN_FILENO);
	close(prev_pipe);
	pipe(pipe_fd);
	dup2(pipe_fd[OUT], STDOUT_FILENO);
	close(pipe_fd[OUT]);
	return (pipe_fd[IN]);
}

static void	exec_in_child(t_cmd *cmd, t_pipeline *pipeline,
							t_env_var **env_list)
{
	int	pid;

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
}

static void	rdir_last_pipe(int pipe_in, t_pipeline *pipeline)
{
	dup2(pipe_in, STDIN_FILENO);
	close(pipe_in);
	dup2(pipeline->std_fd[OUT], STDOUT_FILENO);
}
