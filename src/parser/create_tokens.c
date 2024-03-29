/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 21:03:49 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/28 13:41:07 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_slist	**create_token_list(char *input, t_env_var **env_list)
{
	t_slist	**tokens;

	tokens = get_tokens(input);
	if (tokens == NULL)
		return (NULL);
	clear_empty_tokens(tokens);
	if (check_syntax_errors(tokens) == FAILURE)
	{
		clear_slist(tokens);
		return (NULL);
	}
	tokens = set_tokens_types(tokens);
	tokens = expand_tokens(tokens, env_list);
	if (tokens == NULL)
		return (NULL);
	return (tokens);
}
