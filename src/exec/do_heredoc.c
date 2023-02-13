/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:59:37 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/12 18:30:00 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_hdoc(int *pid);
static void	prompt_hdoc(int hdoc, char *delimiter);
static void	setup_std_fds(int hdoc, int std_out);
static void	set_hdoc_to_in(void);

int	do_heredoc(char *delimiter, t_pipeline *pipeline, t_env_var **env_list)
{
	int	hdoc;
	int	std_out;
	int	pid;

	if (delimiter == NULL)
		return (0);
	std_out = dup(STDOUT_FILENO);
	dup2(pipeline->std_fd[IN], STDIN_FILENO);
	dup2(pipeline->std_fd[OUT], STDOUT_FILENO);
	hdoc = open_hdoc(&pid);
	sig_setup_heredoc(pid);
	if (hdoc == ERROR)
		return (ERROR);
	if (pid == CHILD_ID)
	{
		prompt_hdoc(hdoc, delimiter);
		exit_hdoc_process(hdoc, pipeline, env_list);
	}
	waitpid(pid, NULL, 0);
	setup_std_fds(hdoc, std_out);
	return (0);
}

static int	open_hdoc(int *pid)
{
	int	hdoc;

	*pid = fork();
	if (*pid == ERROR)
		return (ERROR);
	// else if (*pid == CHILD_ID)
	// {
	// 	clear_pipeline(pipeline);
	// 	clear_env_list(env_list);
	// }
	hdoc = open(".heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0600);
	return (hdoc);
}

static void	prompt_hdoc(int hdoc, char *delimiter)
{
	char	*line;

	line = readline("> ");
	while (line && ft_strncmp(delimiter, line, ft_strlen(delimiter) + 1) != 0)
	{
		ft_putendl_fd(line, hdoc);
		free(line);
		line = readline("> ");
		ft_printf("After readline\n");
	}
	if (line == NULL)
	{
		print_heredoc_interrupt(delimiter);
		return ;
	}
	free(line);
}

static void	setup_std_fds(int hdoc, int std_out)
{
	close(hdoc);
	set_hdoc_to_in();
	dup2(std_out, STDOUT_FILENO);
	close(std_out);
}

static void	set_hdoc_to_in(void)
{
	int	hdoc;

	hdoc = open(".heredoc", O_RDONLY);
	unlink(".heredoc");
	dup2(hdoc, STDIN_FILENO);
	close(hdoc);
}
