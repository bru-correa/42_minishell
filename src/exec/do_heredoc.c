/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:59:37 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/26 12:49:53 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <unistd.h>

static int	open_heredoc(int *pid);
static void	prompt_heredoc(int heredoc, char *delimiter);
static void	exit_heredoc(int heredoc, t_pipeline *pipeline,
			t_env_var **env_list);

// TODO:
// Handle heredoc signals
// Run heredoc in child process and waitpid in the end
// Open .heredoc file and redirect to stdin when the child process exits
// Unlink (remove) .heredoc after being used
// Free pipeline and env_var in child process
int	do_heredoc(char *delimiter, t_pipeline *pipeline, t_env_var **env_list)
{
	int	heredoc;
	int	pid;

	if (delimiter == NULL)
		return (0);
	heredoc = open_heredoc(&pid);
	if (heredoc == ERROR)
		return (ERROR);
	if (pid == CHILD_ID)
	{
		prompt_heredoc(heredoc, delimiter);
		exit_heredoc(heredoc, pipeline, env_list);
	}
	// waitpid(pid, NULL, WNOHANG);
	wait(NULL);
	dup2(heredoc, STDIN_FILENO);
	close(heredoc);
	return (0);
}

static int	open_heredoc(int *pid)
{
	int	heredoc;

	*pid = fork();
	if (*pid == ERROR)
		return (ERROR);
	heredoc = open(".heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	return (heredoc);
}

static void	prompt_heredoc(int heredoc, char *delimiter)
{
	char	*line;

	line = readline("> ");
	while (ft_strncmp(delimiter, line, ft_strlen(delimiter) + 1) != 0)
	{
		ft_putstr_fd(line, heredoc);
		free(line);
		line = readline("> ");
	}
	free(line);
}

static void	exit_heredoc(int heredoc, t_pipeline *pipeline,
			t_env_var **env_list)
{
		clear_pipeline(pipeline);
		clear_env_list(env_list);
		close(heredoc);
		exit(0);
}
