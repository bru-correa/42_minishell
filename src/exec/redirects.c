/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:40:06 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/26 12:40:25 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <unistd.h>
#include "string.h"

static int	rdir_file_to_fd(char *filename, int o_flag, int fd);
static int	redirect(t_slist *rdir, t_pipeline *pipeline, t_env_var **env_list);

int	redirect_list(t_slist **rdirs, t_pipeline *pipeline, t_env_var **env_list)
{
	t_slist	*rdir;
	int		status;

	if (rdirs == NULL)
		return (0);
	rdir = *rdirs;
	while (rdir != NULL)
	{
		status = redirect(rdir, pipeline, env_list);
		if (status == ERROR)
		{
			g_exit_status = 1;
			return (ERROR);
		}
		rdir = rdir->next;
	}
	return (0);
}

static int	redirect(t_slist *rdir, t_pipeline *pipeline, t_env_var **env_list)
{
	int	status;

	status = 0;
	if (rdir == NULL)
		return (status);
	else if (rdir->type == T_RDIR_IN)
		status = rdir_file_to_fd(rdir->data, O_RDONLY, STDIN_FILENO);
	else if (rdir->type == T_RDIR_OUT)
		status = rdir_file_to_fd(rdir->data,
				O_WRONLY | O_TRUNC | O_CREAT, STDOUT_FILENO);
	else if (rdir->type == T_RDIR_APPEND)
		status = rdir_file_to_fd(rdir->data,
				O_WRONLY | O_APPEND | O_CREAT, STDOUT_FILENO);
	else if (rdir->type == T_RDIR_HERE)
		status = do_heredoc(rdir->data, pipeline, env_list);
	return (status);
}

// TODO: Need to cancel the current command execution if it fails
static int	rdir_file_to_fd(char *filename, int o_flag, int fd)
{
	int		file;

	file = open(filename, o_flag, 0644);
	if (file == ERROR)
	{
		print_invalid_open(filename);
		return (ERROR);
	}
	dup2(file, fd);
	close(file);
	return (0);
}
