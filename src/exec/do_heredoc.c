/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:59:37 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/26 11:47:09 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_heredoc(char *delimiter)
{
	char	*line;
	int		heredoc;
	int		pid;

	// WARNING: Provisory measury just for testing
	return (0);
	if (delimiter == NULL)
		return (0);
	pid = fork();
	if (pid == ERROR)
		return (ERROR);
	// TODO: run heredoc in child process and waitpid in the end
	// TODO: remove (unlink) .heredoc file
	// TODO: Heredoc signals
	heredoc = open(".heredoc", O_WRONLY | O_TRUNC | O_CREAT);
	if (heredoc == ERROR)
		return (ERROR);
	line = readline("> ");
	while (ft_strncmp(delimiter, line, ft_strlen(delimiter) + 1) != 0)
	{
		ft_putstr_fd(line, heredoc);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(heredoc);
	return (0);
}
