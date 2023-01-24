/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:59:37 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/23 21:51:05 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_heredoc(char *delimiter)
{
	char	*line;
	int		heredoc;
	int		pid;

	// WARNING: Provisory measury just for testing
	return ;
	if (delimiter == NULL)
		return ;
	pid = fork();
	if (pid == ERROR)
		return ;
	// TODO: run heredoc in child process and waitpid in the end
	// TODO: remove (unlink) .heredoc file
	// TODO: Heredoc signals
	heredoc = open(".heredoc", O_WRONLY | O_TRUNC | O_CREAT);
	if (heredoc == ERROR)
		return ;
	line = readline("> ");
	while (ft_strncmp(delimiter, line, ft_strlen(delimiter) + 1) != 0)
	{
		ft_putstr_fd(line, heredoc);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(heredoc);
}
