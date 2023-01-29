/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 04:00:50 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/29 04:01:29 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_hdoc_process(int hdoc, t_pipeline *pipeline,
			t_env_var **env_list)
{
	clear_pipeline(pipeline);
	clear_env_list(env_list);
	close(hdoc);
	exit(0);
}
