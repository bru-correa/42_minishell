/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:12:39 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/23 16:47:59 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_invalid_args(int argc, char **argv);
static void	print_tokens(t_token *token);
static void	print_env_list(t_env_var **env_list);

int	main(int argc, char *argv[], char *envp[])
{
	char		*input;
	t_token		*token_head;
	t_env_var	**env_list;

	if (check_invalid_args(argc, argv) == FAILURE)
		return (1);
	env_list = create_env_with_envp(envp);
	while (1)
	{
		input = readline(">$ ");
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			clear_env_list(env_list);
			exit(0);
		}
		else if (strcmp(input, "env") == 0)
			print_env_list(env_list);
		token_head = get_tokens(input);
		expand_tokens(token_head, env_list);
		token_head = clear_empty_tokens(token_head);
		if (check_syntax_errors(token_head) == SUCCESS)
			print_tokens(token_head);
		free_tokens(token_head);
		free(input);
	}
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

// NOTE: Just for debugging

static void	print_tokens(t_token *token)
{
	t_token	*current_token;

	ft_printf("Tokens:\n");
	current_token = token;
	while (current_token != NULL)
	{
		ft_printf("%s\n", current_token->value);
		current_token = current_token->next;
	}
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
