/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:45:10 by jramondo          #+#    #+#             */
/*   Updated: 2023/01/31 19:41:31 by jramondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_heredoc_child(int signal)
{
	if (signal == SIGINT)
	{
		clean_process();
		printf("\n");
		exit(signal);
	}
}

void	sig_heredoc_parent(int signal)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	clean_process();
	(void)signal;
}