/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 05:17:47 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/13 05:18:56 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_all(t_pipeline *pipeline, t_env_var **env_list)
{
	clear_pipeline(pipeline);
	clear_env_list(env_list);
}
