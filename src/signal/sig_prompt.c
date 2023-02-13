/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:07:17 by jramondo          #+#    #+#             */
/*   Updated: 2023/02/11 18:37:12 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    sig_prompt(int signal)
{
    if(signal == SIGINT)
    {
		ft_putchar_fd('\n', 1);
        rl_replace_line("", 1);
        rl_on_new_line();
        rl_redisplay();
    }
}
