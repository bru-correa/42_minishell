/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 03:13:37 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/13 04:13:30 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_first_cmd(int cmd_index);
static int	is_last_cmd(int cmd_index, int cmd_count);
// static void	create_new_pipe(int *pipe_fds);
// static void	rdir_prev_pipe(int *pipe_fds);

void	set_pipe(int cmd_index, int cmd_count, int default_out)
{
	static int	pipe_fds[2];

	if (is_first_cmd(cmd_index) == FALSE)
	{
		dup2(pipe_fds[IN], STDIN_FILENO);
		close(pipe_fds[IN]);
	}
	if (is_last_cmd(cmd_index, cmd_count) == TRUE)
		dup2(default_out, STDOUT_FILENO);
	else
	{
		pipe(pipe_fds);
		dup2(pipe_fds[OUT], STDOUT_FILENO);
		close(pipe_fds[OUT]);
	}
}

static int	is_first_cmd(int cmd_index)
{
	if (cmd_index == 0)
		return (TRUE);
	return (FALSE);
}

static int	is_last_cmd(int cmd_index, int cmd_count)
{
	if (cmd_index == cmd_count - 1)
		return (TRUE);
	return (FALSE);
}

// static void	create_new_pipe(int *pipe_fds)
// {
// 	pipe(pipe_fds);
// 	dup2(pipe_fds[OUT], STDOUT_FILENO);
// 	close(pipe_fds[OUT]);
// }

// static void	rdir_prev_pipe(int *pipe_fds)
// {
// 	dup2(pipe_fds[IN], STDIN_FILENO);
// 	close(pipe_fds[IN]);
// }
