/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:08:50 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/16 23:33:28 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_args_count(char **args);
static int	check_is_number(char *arg);
static int	get_exit_code(char *arg);

int	repl_exit(t_pipeline *pipeline, t_env_var **env_list)
{
	char	*exit_arg;

	ft_printf("exit\n");
	exit_arg = pipeline->cmds[0]->args[1];
	if (exit_arg != NULL)
	{
		if (check_is_number(exit_arg) == FALSE)
		{
			ft_printf("%s: exit: numeric argument required\n", SHELL_NAME);
			g_exit_status = 2;
		}
		else if (get_args_count(pipeline->cmds[0]->args) > 2)
		{
			ft_printf("%s: exit: too many arguments\n", SHELL_NAME);
			return (1);
		}
		else
			g_exit_status = get_exit_code(exit_arg);
	}
	clear_env_list(env_list);
	clear_pipeline(pipeline);
	rl_clear_history();
	exit(g_exit_status);
}

static int	get_args_count(char **args)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
		i++;
	return (i);
}

static int	get_exit_code(char *arg)
{
	int	length;
	int	i;
	int	result;

	length = ft_strlen(arg);
	i = 0;
	result = 0;
	while (i < length)
	{
		result = (result * 10 + (int)arg[i] - '0') % 256;
		i++;
	}
	return (result);
}

static int	check_is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
