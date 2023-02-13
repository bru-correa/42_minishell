/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:11:24 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/13 03:41:06 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	backup_default_fd(int *default_fd)
{
	default_fd[IN] = dup(STDIN_FILENO);
	default_fd[OUT] = dup(STDOUT_FILENO);
}

void	restore_default_fd(int *default_fd)
{
	dup2(default_fd[IN], STDIN_FILENO);
	dup2(default_fd[OUT], STDOUT_FILENO);
}
