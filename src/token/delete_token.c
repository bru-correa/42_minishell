/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:19:11 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/23 16:32:09 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*delete_token(t_token *token_head, t_token *del_token)
{
	t_token	*prev_token;

	if (token_head == del_token)
	{
		token_head = del_token->next;
		free(del_token->value);
		free(del_token);
		return (token_head);
	}
	prev_token = token_head;
	while (prev_token != NULL)
	{
		if (prev_token->next == del_token)
		{
			prev_token->next = del_token->next;
			break ;
		}
		prev_token = prev_token->next;
	}
	free(del_token->value);
	free(del_token);
	return (token_head);
}
