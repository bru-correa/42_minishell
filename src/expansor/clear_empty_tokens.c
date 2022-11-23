/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_empty_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:36:36 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/23 20:15:25 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_slist	**clear_empty_tokens(t_slist **tokens)
{
	t_slist	*current_token;
	t_slist	*empty_token;

	if (tokens == NULL)
		return (NULL);
	current_token = *tokens;
	while (current_token != NULL)
	{
		if (ft_strncmp(current_token->data, "", 1) == 0)
		{
			empty_token = current_token;
			current_token = current_token->next;
			tokens = delete_from_slist(tokens, empty_token);
		}
		else
			current_token = current_token->next;
	}
	return (tokens);
}
