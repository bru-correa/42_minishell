/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:40:06 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/15 13:40:10 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	redir_file_to_fd(char *filename, int o_flag, int fd)
{
	int	file;

	file = open(filename, o_flag, 0644);
	if (file == ERROR)
		exit_perror(filename, 1);
	dup2(file, fd);
	close(file);
}

void	redir_pipe_to_stdin(int *pipe_fd)
{
	dup2(pipe_fd[READ_END], STDIN_FILENO);
	close(pipe_fd[WRITE_END]);
	close(pipe_fd[READ_END]);
}

void	redir_pipe_to_stdout(int *pipe_fd)
{
	dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
	close(pipe_fd[READ_END]);
	close(pipe_fd[WRITE_END]);
}

void	create_pipe_and_fork(int *pipe_fd, pid_t *pid)
{
	if (pipe(pipe_fd) == ERROR)
		exit_perror("ERROR: Could not open pipe\n", 1);
	*pid = fork();
	if (*pid == ERROR)
		exit_perror("ERROR: Failed to handle fork\n", 1);
}
