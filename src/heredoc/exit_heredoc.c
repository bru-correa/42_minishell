/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 04:00:50 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/14 00:50:49 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	force_interrupt(void);

void	exit_hdoc_process(t_pipeline *pipeline, t_env_var **env_list)
{
	clear_fds();
	clear_pipeline(pipeline);
	clear_env_list(env_list);
	if (g_exit_status == 130)
		force_interrupt();
	exit(0);
}

static void	force_interrupt(void)
{
	sig_reset_interrupt();
	kill(0, SIGINT);
}
