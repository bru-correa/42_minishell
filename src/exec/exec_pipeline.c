/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 10:02:22 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/05 21:29:36 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static void	exec_cmd(t_cmd *cmd, t_env_var **env_list, t_pipeline *pipeline);
static void	print_invalid_cmd(t_cmd *cmd);

void	exec_pipeline(t_pipeline *pipeline, t_env_var **env_list)
{
	int	i;

	// Exec first cmd
	i = pipeline->cmd_index;
	exec_cmd(pipeline->cmds[i], env_list, pipeline);
}

static void	exec_cmd(t_cmd *cmd, t_env_var **env_list, t_pipeline *pipeline)
{
	char	**envp;	
	char	*cmd_path;

	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		repl_exit(pipeline, env_list);
	envp = get_env_array(env_list);
	cmd_path = get_cmd_path(cmd->args[0], envp);
	if (cmd_path == NULL)
	{
		print_invalid_cmd(cmd);
		return ;
	}
	execve(cmd_path, cmd->args, envp);
}

static void	print_invalid_cmd(t_cmd *cmd)
{
	ft_putstr_fd(cmd->args[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	g_minish.status_code = 127;
}
