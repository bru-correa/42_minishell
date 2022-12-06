/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:52:50 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/06 18:06:46 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tokens(t_slist **tokens);

t_slist	**expand_tokens(t_slist **tokens, t_env_var **env_list)
{
	if (check_syntax_errors(tokens) == FAILURE)
	{
		clear_slist(tokens);
		return (NULL);
	}
	expand_variables(tokens, env_list);
	remove_quotes(tokens);
	tokens = clear_empty_tokens(tokens);
	if (*tokens == NULL)
	{
		clear_slist(tokens);
		return (NULL);
	}
	print_tokens(tokens);
	return (tokens);
}

// NOTE: Just for debugging
static void	print_tokens(t_slist **tokens)
{
	t_slist	*current_token;

	ft_printf("Tokens:\n");
	current_token = *tokens;
	while (current_token != NULL)
	{
		ft_printf("%s\n", current_token->data);
		current_token = current_token->next;
	}
}
