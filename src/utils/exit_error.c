/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:35:52 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/21 12:54:26 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error_token(t_slist **tokens)
{
	clear_slist(tokens);
	ft_putstr_fd("Error: Could not create tokens!\n", STDERR_FILENO);
	exit(1);
}

void	exit_perror(char *msg, int error_code)
{
	perror(msg);
	exit(error_code);
}
