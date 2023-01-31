/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_parent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:40:42 by jramondo          #+#    #+#             */
/*   Updated: 2023/01/31 14:44:19 by jramondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_parent(int signal)
{
	if (signal == SIGINT)
		printf("\n");
	else if (signal == SIGQUIT)
		ft_putstr_fd("Quit\n", STDERR_FILENO);
	cleanup_process();
}