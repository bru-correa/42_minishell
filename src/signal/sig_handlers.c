/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:08:31 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/12 16:36:19 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handle_prompt(int signal)
{
	(void)signal;
	clean_process();
	g_exit_status = 130;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}
