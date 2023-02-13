/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:08:42 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/13 05:38:54 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_in_child(t_cmd *cmd, t_pipeline *pipeline,
				t_env_var **env_list);
static int	*init_children_pid(int cmd_count);
static void	handle_redirects(t_slist **rdir_list, t_pipeline *pipeline,
				t_env_var **env_list);

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
