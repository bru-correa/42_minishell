/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:32:55 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/26 10:58:53 by bcorrea-         ###   ########.fr       */
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
	node->type = 0;
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

	if (list == NULL)
		return (NULL);
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
	t_slist	*current;

	if (*list == node)
	{
		*list = node->next;
		free_slist_node(node);
		return (list);
	}
	current = *list;
	while (current != NULL)
	{
		if (current->next == node)
		{
			current->next = node->next;
			break ;
		}
		current = current->next;
	}
	free_slist_node(node);
	return (list);
}
