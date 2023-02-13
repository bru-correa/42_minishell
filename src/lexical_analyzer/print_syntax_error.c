/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:55:35 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/13 04:53:59 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(char *invalid_data)
{
	ft_putstr_fd("mini$HELL: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(invalid_data, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void	print_quote_error(void)
{
	ft_putstr_fd("mini$HELL: ", STDERR_FILENO);
	ft_putstr_fd("can't have open quotes", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	print_special_char_error(char c)
{
	ft_putstr_fd("mini$HELL: ", STDERR_FILENO);
	ft_putstr_fd("invalid special character ", STDERR_FILENO);
	ft_putchar_fd(c, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
