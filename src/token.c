/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:32:55 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/10/31 14:51:34 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->value = value;
	token->next = NULL;
	return (token);
}

t_token	*append_token(t_token *token_head, char *value)
{
	t_token	*current_token;
	t_token	*new_token;

	new_token = create_token(value);
	if (new_token == NULL)
	{
		free_tokens(token_head);
		return (NULL);
	}
	if (token_head == NULL)
		return (new_token);
	current_token = token_head;
	while (current_token->next != NULL)
		current_token = current_token->next;
	current_token->next = new_token;
	return (token_head);
}

t_token	*free_tokens(t_token *token_head)
{
	t_token	*current_token;
	t_token	*previous_token;

	current_token = token_head;
	while (current_token != NULL)
	{
		previous_token = current_token;
		current_token = current_token->next;
		free(previous_token->value);
		free(previous_token);
	}
	return (NULL);
}
