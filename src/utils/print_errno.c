/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errno.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:56:56 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/13 04:53:22 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <string.h>
#include <unistd.h>

void	print_invalid_open(char *filename)
{
	char	*error_msg;

	error_msg = strerror(errno);
	ft_putstr_fd("mini$HELL: ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
