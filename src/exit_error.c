/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:11:57 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/23 19:45:14 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error_token(t_slist **tokens)
{
	clear_slist(tokens);
	ft_putstr_fd("Error: Could not create tokens!\n", STDERR_FILENO);
	exit(1);
}
