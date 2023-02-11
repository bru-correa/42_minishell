/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:02:26 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/11 15:06:19 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_args(char **args);

void	clear_pipeline(t_pipeline *pipeline)
{
	int	i;

	if (pipeline == NULL)
		return ;
	close(pipeline->std_fd[IN]);
	close(pipeline->std_fd[OUT]);
	i = 0;
	while (pipeline->cmds[i] != NULL)
	{
		clear_args(pipeline->cmds[i]->args);
		clear_slist(pipeline->cmds[i]->rdir_list);
		free(pipeline->cmds[i]);
		i++;
	}
	free(pipeline->cmds);
	free(pipeline);
}

static void	clear_args(char **args)
{
	int	i;

	if (args == NULL)
		return ;
	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}
