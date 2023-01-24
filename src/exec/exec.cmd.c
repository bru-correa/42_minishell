/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:46:28 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/16 13:19:24 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

void	exec_cmd(t_cmd *cmd, t_env_var **env_list, t_pipeline *pipeline)
{
	char	**envp;	
	char	*cmd_path;
	int		pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid != CHILD_ID)
		return;
	envp = get_env_array(env_list);
	cmd_path = get_cmd_path(cmd->args[0], envp);
	if (cmd_path == NULL)
	{
		// TODO: Create function exit_invalid_cmd
		print_invalid_cmd(cmd);
		exit(127);
	}
	execve(cmd_path, cmd->args, envp);
	clear_env_list(env_list);
	clear_pipeline(pipeline);
	exit(1);
	// TODO: exit perror
}
