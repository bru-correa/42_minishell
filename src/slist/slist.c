/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:32:55 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/23 20:35:18 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_slist	**create_slist(void)
{
	t_slist	**list;

	list = malloc(sizeof(t_list *));
	if (list == NULL)
		return (NULL);
	*list = NULL;
	return (list);
}

t_slist	*create_slist_node(char *data)
{
	t_slist	*node;

	node = malloc(sizeof(t_slist));
	if (node == NULL)
		return (NULL);
	node->data = data;
	node->next = NULL;
	return (node);
}

t_slist	**append_to_slist(t_slist **list, char *data)
{
	t_slist	*current_node;
	t_slist	*new_node;

	if (list == NULL)
		return (NULL);
	new_node = create_slist_node(data);
	if (new_node == NULL)
		return (list);
	if (*list == NULL)
	{
		*list = new_node;
		return (list);
	}
	current_node = *list;
	while (current_node->next != NULL)
		current_node = current_node->next;
	current_node->next = new_node;
	return (list);
}

t_slist	**clear_slist(t_slist **list)
{
	t_slist	*current_node;
	t_slist	*prev_node;

	current_node = *list;
	while (current_node != NULL)
	{
		prev_node = current_node;
		current_node = current_node->next;
		free_slist_node(prev_node);
	}
	free(list);
	return (NULL);
}

t_slist	**delete_from_slist(t_slist **list, t_slist *node)
{
	t_slist	*prev_node;

	if (*list == node)
	{
		*list = node->next;
		free_slist_node(node);
		return (list);
	}
	prev_node = *list;
	while (prev_node != NULL)
	{
		if (prev_node->next == node)
		{
			prev_node->next = node->next;
			break ;
		}
		prev_node = prev_node->next;
	}
	free_slist_node(node);
	return (list);
}
