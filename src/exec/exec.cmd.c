/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:46:28 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/16 23:49:04 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

static void	clear_envp(char **envp);
static void	clear_memory(char **envp, t_env_var **env_list,
				t_pipeline *pipeline);

void	exec_cmd(t_cmd *cmd, t_env_var **env_list, t_pipeline *pipeline)
{
	char	**envp;	
	char	*cmd_path;

	if (cmd == NULL || cmd->args == NULL)
		exit(0);
	envp = get_env_array(env_list);
	cmd_path = get_cmd_path(cmd->args[0], envp);
	if (cmd_path == NULL)
	{
		clear_envp(envp);
		exit_invalid_cmd(cmd, env_list, pipeline);
	}
	execve(cmd_path, cmd->args, envp);
	clear_memory(envp, env_list, pipeline);
	free(cmd_path);
	exit(EXIT_FAILURE);
}

static void	clear_memory(char **envp, t_env_var **env_list,
	t_pipeline *pipeline)
{
	clear_env_list(env_list);
	clear_pipeline(pipeline);
	clear_envp(envp);
}

static void	clear_envp(char **envp)
{
	int	i;

	if (envp == NULL)
		return ;
	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
