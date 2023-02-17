/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramondo <jramondo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:12:39 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/17 05:16:03 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>

static int	check_invalid_args(int argc, char **argv);

int	g_exit_status;

int	main(int argc, char *argv[], char *envp[])
{
	t_env_var	**env_list;

	if (check_invalid_args(argc, argv) == FAILURE)
		return (EXIT_FAILURE);
	env_list = create_env_with_envp(envp);
	g_exit_status = 0;
	welcome(env_list);
	repl(env_list);
	clear_env_list(env_list);
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
