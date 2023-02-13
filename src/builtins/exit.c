/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:08:50 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/11 15:37:38 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	repl_exit(t_pipeline *pipeline, t_env_var **env_list)
{
	clear_env_list(env_list);
	clear_pipeline(pipeline);
	rl_clear_history();
	exit(0);
}
