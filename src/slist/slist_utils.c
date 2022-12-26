/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slist_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:18:28 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/26 12:17:58 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_slist	*free_slist_node(t_slist *node)
{
	free(node->data);
	free(node);
	return (NULL);
}

t_slist	*pop_slist_node(t_slist **list, t_slist *node)
{
	t_slist	*current;

	if (list == NULL)
	{
		node->next = NULL;
		return (node);
	}
	if (*list == node)
	{
		*list = node->next;
		node->next = NULL;
		return (node);
	}
	current = *list;
	while (current->next != NULL)
	{
		if (current->next == node)
		{
			current->next = node->next;
			break ;
		}
		current = current->next;
	}
	node->next = NULL;
	return (node);
}

t_slist	**append_node_to_slist(t_slist **list, t_slist *node)
{
	t_slist	*current_node;

	if (list == NULL)
		return (NULL);
	if (*list == NULL)
	{
		*list = node;
		return (list);
	}
	current_node = *list;
	while (current_node->next != NULL)
		current_node = current_node->next;
	current_node->next = node;
	return (list);
}
