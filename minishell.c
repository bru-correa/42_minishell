/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:12:39 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/05 21:27:34 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_invalid_args(int argc, char **argv);

t_minish	g_minish;

int	main(int argc, char *argv[], char *envp[])
{
	if (check_invalid_args(argc, argv) == FAILURE)
		return (1);
	g_minish.env_list = create_env_with_envp(envp);
	g_minish.status_code = 0;
	repl();
	return (0);
}

static int	check_invalid_args(int argc, char **argv)
{
	if (argc > 1)
	{
		ft_putstr_fd("Invalid argument: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (FAILURE);
	}
	return (SUCCESS);
}
