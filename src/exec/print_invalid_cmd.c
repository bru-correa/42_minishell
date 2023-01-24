/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_invalid_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:47:40 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/23 21:24:34 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_invalid_cmd(t_cmd *cmd)
{
	ft_putstr_fd(cmd->args[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	g_exit_status = 127;
}
