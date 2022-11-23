/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_empty_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:36:36 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/23 17:09:49 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*clear_empty_tokens(t_token *token_head)
{
	t_token	*current_token;
	t_token	*empty_token;

	if (token_head == NULL)
		return (NULL);
	current_token = token_head;
	while (current_token != NULL)
	{
		if (ft_strncmp(current_token->value, "", 1) == 0)
		{
			empty_token = current_token;
			current_token = current_token->next;
			token_head = delete_token(token_head, empty_token);
		}
		else
			current_token = current_token->next;
	}
	return (token_head);
}
