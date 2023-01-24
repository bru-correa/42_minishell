/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:40:06 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/23 21:22:48 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <unistd.h>

static void	rdir_file_to_fd(char *filename, int o_flag, int fd);

void	redirect_list(t_slist **rdirs)
{
	t_slist	*rdir;

	// WARNING: Provisory measure just for testing!!!
	return ;
	if (rdirs == NULL)
		return ;
	rdir = *rdirs;
	while (rdir != NULL)
	{
		redirect(rdir);
		rdir = rdir->next;
	}
}

void	redirect(t_slist *rdir)
{
	if (rdir == NULL)
		return ;
	else if (rdir->type == T_RDIR_IN)
		rdir_file_to_fd(rdir->data, O_RDONLY, STDIN_FILENO);
	else if (rdir->type == T_RDIR_OUT)
		rdir_file_to_fd(rdir->data,
				O_WRONLY | O_TRUNC | O_CREAT, STDOUT_FILENO);
	else if (rdir->type == T_RDIR_APPEND)
		rdir_file_to_fd(rdir->data,
				O_WRONLY | O_APPEND | O_CREAT, STDOUT_FILENO);
	else if (rdir->type == T_RDIR_HERE)
		do_heredoc(rdir->data);
}

static void	rdir_file_to_fd(char *filename, int o_flag, int fd)
{
	int	file;

	file = open(filename, o_flag, 0644);
	if (file == ERROR)
		exit_perror(filename, 1);
	dup2(file, fd);
	close(file);
}
