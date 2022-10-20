/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bcorrea->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:36:04 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/10/19 21:54:41 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(int type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

t_token	*add_token(t_token *token, int type, char *value)
{
	t_token	*new_token;
	t_token	*current_token;

	new_token = create_token(type, value);
	current_token = token;
	if (new_token == NULL)
	{
		free_tokens(token);
		return (NULL);
	}
	if (current_token == NULL)
		return (new_token);
	while (current_token->next != NULL)
		current_token = current_token->next;
	current_token->next = new_token;
	return (token);
}

t_token	*free_tokens(t_token *token)
{
	t_token	*current_token;
	t_token	*previous_token;

	current_token = token;
	while (current_token != NULL)
	{
		previous_token = current_token;
		current_token = current_token->next;
		free(previous_token->value);
		free(previous_token);
	}
	return (NULL);
}
