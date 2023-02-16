/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:08:42 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/15 23:12:42 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_in_child(t_cmd *cmd, t_pipeline *pipeline,
				t_env_var **env_list);
static int	handle_redirects(t_slist **rdir_list, t_pipeline *pipeline,
				t_env_var **env_list);

void	exec_pipeline(t_pipeline *pipeline, t_env_var **env_list)
{
	int		i;
	t_cmd	*cmd;
	int		status;

	i = 0;
	while (i < pipeline->cmd_count)
	{
		cmd = pipeline->cmds[i];
		set_pipe(i, pipeline->cmd_count, pipeline->default_fd[OUT]);
		status = handle_redirects(cmd->rdir_list, pipeline, env_list);
		if (status == ERROR)
		{
			i++;
			continue;
		}
		else if (status == INTERRUPT)
			return ;
		pipeline->children_pids[i] = fork();
		sig_setup_exec(pipeline->children_pids[i]);
		if (pipeline->children_pids[i] == CHILD_ID)
			exec_in_child(cmd, pipeline, env_list);
		i++;
	}
	restore_default_fd(pipeline->default_fd);
	wait_for_children(pipeline->children_pids, pipeline->cmd_count);
}

static void	exec_in_child(t_cmd *cmd, t_pipeline *pipeline,
				t_env_var **env_list)
{
	clear_fds();
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

static int	handle_redirects(t_slist **rdir_list, t_pipeline *pipeline,
				t_env_var **env_list)
{
	int	status;

	status = redirect_list(rdir_list, pipeline, env_list);
	if (status == 0)
		return (0);
	restore_default_fd(pipeline->default_fd);
	if (status == ERROR)
		return (ERROR);
	else if (status == INTERRUPT)
		return (INTERRUPT);
	return (0);
}
