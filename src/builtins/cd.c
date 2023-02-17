/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 02:59:25 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/17 06:00:18 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *dir_path, char *error_msg);
static int	change_dir_to_home(t_env_var **env_list);
static int	change_dir_to_path(char *dir_path, t_env_var **env_list);

int	builtin_cd(t_cmd *cmd, t_env_var **env_list)
{
	char	*dir_path;
	int		status;

	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("mini$HELL: cd: too many arguments\n", EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	dir_path = cmd->args[1];
	status = 0;
	if (dir_path == NULL)
		status = change_dir_to_home(env_list);
	else
		status = change_dir_to_path(dir_path, env_list);
	return (status);
}

static int	change_dir_to_home(t_env_var **env_list)
{
	int		status;
	char	*dir_path;

	dir_path = search_env_var(env_list, "HOME");
	if (ft_strncmp(dir_path, "", 1) == 0)
		status = change_dir_to_path("/", env_list);
	else
		status = change_dir_to_path(dir_path, env_list);
	free(dir_path);
	return (status);
}

static int	change_dir_to_path(char *dir_path, t_env_var **env_list)
{
	char	*buffer;
	char	*new_pwd;
	char	*old_pwd;

	buffer = NULL;
	old_pwd = getcwd(buffer, 0);
	add_var_to_env(env_list, "OLDPWD", old_pwd);
	free(old_pwd);
	if (chdir(dir_path) == ERROR)
	{
		print_error(dir_path, strerror(errno));
		return (errno);
	}
	new_pwd = getcwd(buffer, 0);
	add_var_to_env(env_list, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}

static void	print_error(char *dir_path, char *error_msg)
{
	ft_putstr_fd("mini$HELL: ", STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(dir_path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
