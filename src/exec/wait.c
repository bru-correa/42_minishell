/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 05:37:10 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/18 15:36:52 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_for_child(int child_pid)
{
	int	status;

	status = 0;
	waitpid(child_pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (status == SIGINT || status == SIGQUIT)
			ft_printf("\n");
		else if (status == 130 || status == 131)
		{
			ft_printf("\n");
			return (status);
		}
		return (status + 128);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

void	wait_for_children(int *children_pid, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		if (children_pid[i] != 0)
			g_exit_status = wait_for_child(children_pid[i]);
		i++;
	}
}
