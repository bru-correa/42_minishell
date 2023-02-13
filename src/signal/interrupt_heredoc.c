/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interrupt_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 00:59:20 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/12 16:58:59 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// WARNING: Not being used
void	interrupt_hdoc(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	g_exit_status = 130;
	exit(130);
}

// TODO: Move to heredoc folder
void	print_heredoc_interrupt(char *delimiter)
{
	ft_putstr_fd("warning: ", OUT);
	ft_putstr_fd("here-document delimited by end-of-file ", OUT);
	ft_putstr_fd("(wanted `", OUT);
	ft_putstr_fd(delimiter, OUT);
	ft_putstr_fd("')\n", OUT);
}
