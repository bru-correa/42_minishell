/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:12:39 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/06 18:22:41 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_invalid_args(int argc, char **argv);
static void	print_env_list(t_env_var **env_list);
static void	simple_exit(char *input, t_env_var **env_list);

int	main(int argc, char *argv[], char *envp[])
{
	char		*input;
	t_env_var	**env_list;

	if (check_invalid_args(argc, argv) == FAILURE)
		return (1);
	env_list = create_env_with_envp(envp);
	while (1)
	{
		input = readline(">$ ");
		if (strcmp(input, "exit") == 0)
			simple_exit(input, env_list);
		else if (strcmp(input, "env") == 0)
			print_env_list(env_list);
		parse_input(input, env_list);
		free(input);
	}
	return (0);
}

static void	simple_exit(char *input, t_env_var **env_list)
{
	free(input);
	clear_env_list(env_list);
	exit(0);
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

static void	print_env_list(t_env_var **env_list)
{
	t_env_var	*current_var;

	if (env_list == NULL)
		return ;
	current_var = *env_list;
	while (current_var != NULL)
	{
		ft_printf("%s=", current_var->key);
		ft_printf("%s\n", current_var->value);
		current_var = current_var->next;
	}
}
