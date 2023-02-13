/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:28:30 by jramondo          #+#    #+#             */
/*   Updated: 2023/02/11 17:46:21 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    set_signal(void (*handler)(int), int signal)
{
    struct sigaction	action;

    ft_memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = handler;
    // action.sa_flags = SA_RESTART;
    sigemptyset(&action.sa_mask);
    sigaction(signal, &action, NULL);
}
