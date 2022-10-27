/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:12:39 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/10/27 20:45:21 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tokens(t_token *token);

int	main(void)
{
	char	*input;
	t_token	*token;

	while (1)
	{
		input = readline(">$ ");
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			exit(0);
		}
		token = get_tokens(input);
		print_tokens(token);
		free_tokens(token);
		free(input);
	}
	return (0);
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
