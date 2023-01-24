/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:08:50 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/23 23:06:16 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	repl_exit(t_pipeline *pipeline, t_env_var **env_list)
{
	clear_env_list(env_list);
	clear_pipeline(pipeline);
	clear_history();
	exit(0);
}
