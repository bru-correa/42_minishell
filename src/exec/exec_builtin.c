/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:03:26 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/18 01:36:39 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	is_cmd_valid(t_cmd *cmd);
static void	exit_builtin(int status, t_pipeline *pipeline,
				t_env_var **env_list);

void	exec_builtin(t_cmd *cmd, t_env_var **env_list, t_pipeline *pipeline)
{
	int	status;

	status = 0;
	if (is_cmd_valid(cmd) == FALSE)
		return ;
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		status = repl_exit(pipeline, env_list);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		status = echo(cmd);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		status = builtin_cd(cmd, env_list);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		status = env(env_list);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		status = builtin_export(cmd, env_list);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		status = builtin_unset(cmd, env_list);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		status = builtin_pwd();
	exit_builtin(status, pipeline, env_list);
}

static int	is_cmd_valid(t_cmd *cmd)
{
	if (cmd == NULL)
		return (FALSE);
	else if (cmd->args[0] == NULL)
		return (FALSE);
	return (TRUE);
}

static void	exit_builtin(int status, t_pipeline *pipeline,
				t_env_var **env_list)
{
	g_exit_status = status;
	if (pipeline->cmd_count > 1)
	{
		clear_pipeline(pipeline);
		clear_env_list(env_list);
		exit(status);
	}
}
