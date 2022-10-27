/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_delimiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:49:10 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/10/27 20:10:19 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_append(const char *cmdline, int current, int start);
static int	check_heredoc(const char *cmdline, int current, int start);
static int	check_pipe(int current, int start);

int	get_delimiter_index(const char *cmdline, int current, int start)
{
	if (cmdline[current] == ' ')
		return (current);
	else if (cmdline[current] == '|')
		return (check_pipe(current, start));
	else if (cmdline[current] == '>')
		return (check_append(cmdline, current, start));
	else if (cmdline[current] == '<')
		return (check_heredoc(cmdline, current, start));
	return (-1);
}

static int	check_pipe(int current, int start)
{
	if (current != start)
		return (current);
	else
		return (current + 1);
}

// Return the index after the operator when the operator is at the start
static int	check_append(const char *cmdline, int current, int start)
{
	if (current != start)
		return (current);
	else if (cmdline[current + 1] == '>')
		return (current + 2);
	else
		return (current + 1);
}

// Return the index after the operator when the operator is at the start
static int	check_heredoc(const char *cmdline, int current, int start)
{
	if (current != start)
		return (current);
	else if (cmdline[current + 1] == '<')
		return (current + 2);
	else
		return (current + 1);
}
