/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:11:24 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/19 12:15:09 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	backup_std_fd(int *std_fd)
{
	std_fd[IN] = dup(STDIN_FILENO);
	std_fd[OUT] = dup(STDOUT_FILENO);
}

void	restore_std_fd(int *std_fd)
{
	dup2(std_fd[IN], STDIN_FILENO);
	dup2(std_fd[OUT], STDOUT_FILENO);
}
