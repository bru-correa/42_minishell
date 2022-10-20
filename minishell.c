/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bcorrea->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:24:27 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/10/19 21:52:57 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tokens(t_token *token);

int	main(void)
{
	char	*input;
	char	*cwd;
	t_token	*token;

	while (1)
	{
		input = readline(">$ ");
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			exit(0);
		}
		else if (strncmp(input, "cd", 2) == 0)
		{
			cwd = NULL;
			chdir(getenv("HOME"));
			cwd = getcwd(cwd, 0);
			printf("%s\n", cwd);
			free(cwd);
		}
		else
		{
			token = get_tokens(input);
			print_tokens(token);
			free_tokens(token);
		}
		free(input);
	}
	return (0);
}

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
