/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:08:31 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/14 00:48:57 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handle_prompt(int signal)
{
	(void)signal;
	clear_fds();
	g_exit_status = 130;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_handle_heredoc(int signal)
{
	(void)signal;
	g_exit_status = 130;
	ft_putstr_fd("\n", STDIN_FILENO);
	rl_replace_line("", 1);
	close(STDIN_FILENO);
}
