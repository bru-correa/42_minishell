/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:12:39 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/19 13:03:12 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_invalid_args(int argc, char **argv);

int	main(int argc, char *argv[], char *envp[])
{
	t_env_var	**env_list;

	if (check_invalid_args(argc, argv) == FAILURE)
		return (1);
	env_list = create_env_with_envp(envp);
	repl(env_list);
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
