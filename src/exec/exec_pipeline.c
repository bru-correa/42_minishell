/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:08:42 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/13 05:20:55 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_in_child(t_cmd *cmd, t_pipeline *pipeline,
				t_env_var **env_list);
static void	wait_for_children(int *children_pid);
static int	*init_children_pid(int cmd_count);
static int	wait_for_child(int child_pid);
static void	handle_redirects(t_slist **rdir_list, t_pipeline *pipeline,
				t_env_var **env_list);

// TODO: New execution pipeline
// * Exit inside redirect list, in case of error in redirect
// * Clean all the unnecessary file descriptors in child process, after
// opening the pipe
void	exec_pipeline(t_pipeline *pipeline, t_env_var **env_list)
{
	int		*children_pid;
	int		i;
	t_cmd	*cmd;

	backup_default_fd(pipeline->default_fd);
	children_pid = init_children_pid(pipeline->cmd_count);
	i = 0;
	while (i < pipeline->cmd_count)
	{
		cmd = pipeline->cmds[i];
		set_pipe(i, pipeline->cmd_count, pipeline->default_fd[OUT]);
		children_pid[i] = fork();
		sig_setup_exec(children_pid[i]);
		if (children_pid[i] == CHILD_ID)
		{
			free(children_pid);
			clear_fds();
			handle_redirects(cmd->rdir_list, pipeline, env_list);
			exec_in_child(cmd, pipeline, env_list);
		}
		i++;
	}
	restore_default_fd(pipeline->default_fd);
	wait_for_children(children_pid);
}

static void	exec_in_child(t_cmd *cmd, t_pipeline *pipeline,
				t_env_var **env_list)
{
	if (cmd->args == NULL)
	{
		clear_all(pipeline, env_list);
		exit(0);
	}
	if (is_builtin(cmd->args[0]))
		exec_builtin(cmd, env_list, pipeline);
	else
		exec_cmd(cmd, env_list, pipeline);
}

static int	*init_children_pid(int cmd_count)
{
	int	*children_pid;
	int	length;

	length = sizeof(int) * (cmd_count + 1);
	children_pid = malloc(length);
	if (children_pid == NULL)
		return (NULL);
	ft_bzero(children_pid, length);
	return (children_pid);
}

static int	wait_for_child(int child_pid)
{
	int	status;

	status = 0;
	waitpid(child_pid, &status, 0);
	if (WIFSIGNALED(status))
		return (status + 128);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

static void	wait_for_children(int *children_pid)
{
	int	i;

	i = 0;
	while(children_pid[i] != 0)
	{
		g_exit_status = wait_for_child(children_pid[i]);
		i++;
	}
	free(children_pid);
}

static void	handle_redirects(t_slist **rdir_list, t_pipeline *pipeline,
				t_env_var **env_list)
{
	if (redirect_list(rdir_list, pipeline, env_list) == ERROR)
	{
		clear_env_list(env_list);
		clear_pipeline(pipeline);
		exit(1);
	}
}
