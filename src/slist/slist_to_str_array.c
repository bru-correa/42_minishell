/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slist_to_str_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:27:02 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/23 12:26:31 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_slist_count(t_slist **list);
static char	*get_next_str(t_slist **list);

char	**slist_to_str_array(t_slist **list)
{
	int		count;
	char	**strs;
	int		i;

	if (list == NULL)
		return (NULL);
	else if (*list == NULL)
	{
		free(list);
		return (NULL);
	}
	count = get_slist_count(list);
	strs = malloc(sizeof(char *) * (count + 1));
	if (strs == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		strs[i] = get_next_str(list);
		i++;
	}
	strs[i] = NULL;
	clear_slist(list);
	return (strs);
}

static int	get_slist_count(t_slist **list)
{
	t_slist	*current;
	int		count;

	count = 0;
	current = *list;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static char	*get_next_str(t_slist **list)
{
	char	*str;

	str = ft_strdup((*list)->data);
	delete_from_slist(list, *list);
	return (str);
}
