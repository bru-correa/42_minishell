/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hdoc_warning.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 00:59:20 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/13 03:57:55 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Move to heredoc folder
void	print_hdoc_warning(char *delimiter)
{
	ft_putstr_fd("warning: ", OUT);
	ft_putstr_fd("here-document delimited by end-of-file ", OUT);
	ft_putstr_fd("(wanted `", OUT);
	ft_putstr_fd(delimiter, OUT);
	ft_putstr_fd("')\n", OUT);
}
