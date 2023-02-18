/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:43:06 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/18 00:31:01 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_variables(char **args, t_env_var **env_list);
static int	set_variable(char *arg, t_env_var **env_list);
static char	*get_key(char *arg);
static char	*get_value(char *arg);

int	builtin_export(t_cmd *cmd, t_env_var **env_list)
{
	if (cmd->args[1])
		return (set_variables(cmd->args, env_list));
	else
	{
		print_export(env_list);
		return (0);
	}
}

static int	set_variables(char **args, t_env_var **env_list)
{
	int	i;
	int	status;

	i = 1;
	while (args[i])
	{
		status = set_variable(args[i], env_list);
		i++;
	}
	return (status);
}

static int	set_variable(char *arg, t_env_var **env_list)
{
	char	*key;
	char	*value;

	if (check_var_name(arg) == FALSE)
		return (EXIT_FAILURE);
	else if (ft_strchr(arg, '=') == NULL)
	{
		add_var_to_env(env_list, arg, "");
		return (EXIT_SUCCESS);
	}
	key = get_key(arg);
	value = get_value(arg);
	add_var_to_env(env_list, key, value);
	free(key);
	free(value);
	return (EXIT_SUCCESS);
}

static char	*get_key(char *arg)
{
	char	*key;
	int		size;

	size = 0;
	while (arg[size] != '=')
		size++;
	key = ft_substr(arg, 0, size);
	return (key);
}

static char	*get_value(char *arg)
{
	char	*value;
	int		i;
	int		start;
	int		length;

	i = 0;
	while (arg[i] != '=')
		i++;
	start = i + 1;
	if (arg[start] == '\0')
		return (ft_strdup(""));
	length = ft_strlen(&arg[start]);
	value = ft_substr(arg, start, length);
	return (value);
}
