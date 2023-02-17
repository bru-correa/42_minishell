/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:53:02 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/16 23:48:13 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_setup_prompt(void)
{
	struct sigaction	act_int;
	struct sigaction	act_quit;

	ft_bzero(&act_int, sizeof(struct sigaction));
	ft_bzero(&act_quit, sizeof(struct sigaction));
	sigemptyset(&act_int.sa_mask);
	sigemptyset(&act_quit.sa_mask);
	act_int.sa_handler = sig_handle_prompt;
	act_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act_int, NULL);
	sigaction(SIGQUIT, &act_quit, NULL);
}

void	sig_setup_exec(int pid)
{
	struct sigaction	act;

	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	if (pid == CHILD_ID)
		act.sa_handler = SIG_DFL;
	else
		act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	sig_setup_heredoc(int pid)
{
	struct sigaction	act_int;
	struct sigaction	act_quit;

	sigemptyset(&act_int.sa_mask);
	sigemptyset(&act_quit.sa_mask);
	act_int.sa_flags = 0;
	act_quit.sa_flags = 0;
	if (pid == CHILD_ID)
		act_int.sa_handler = sig_handle_heredoc;
	else
		act_int.sa_handler = SIG_IGN;
	act_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act_int, NULL);
	sigaction(SIGQUIT, &act_quit, NULL);
}

void	sig_reset_interrupt(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = SIG_DFL;
	sigaction(SIGINT, &act, NULL);
}
