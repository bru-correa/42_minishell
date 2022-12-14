/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:52:50 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/15 15:53:59 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_slist	**expand_tokens(t_slist **tokens, t_env_var **env_list)
{
	expand_variables(tokens, env_list);
	remove_quotes(tokens);
	tokens = clear_empty_tokens(tokens);
	if (*tokens == NULL)
	{
		clear_slist(tokens);
		return (NULL);
	}
	return (tokens);
}
