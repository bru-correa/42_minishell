/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:35:52 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/01 22:00:35 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error_token(t_slist **tokens)
{
	clear_slist(tokens);
	ft_putstr_fd("Error: Could not create tokens!\n", STDERR_FILENO);
	exit(1);
}

void	exit_perror(char *msg, int error_code)
{
	perror(msg);
	exit(error_code);
}

void	exit_invalid_cmd(t_cmd *cmd, t_env_var **env_list, t_pipeline *pipeline)
{
	ft_putstr_fd(cmd->args[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	g_exit_status = 127;
	clear_pipeline(pipeline);
	clear_env_list(env_list);
	exit(127);
}
