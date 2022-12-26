/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:39:11 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/19 13:04:42 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// WARNING: Unused function
t_slist	**split_tokens(t_slist *start_token)
{
	t_slist	**sub_tokens;
	t_slist	*current;

	if (start_token == NULL)
		return (NULL);
	sub_tokens = create_slist();
	if (sub_tokens == NULL)
		return (NULL);
	current = start_token;
	while (current != NULL && current->data[0] != '|')
	{
		append_to_slist(sub_tokens, ft_strdup(current->data));
		if (current->data[0] != '|')
		{
			current = current->next;
			break ;
		}
		current = current->next;
	}
	start_token = current;
	return (sub_tokens);
}
