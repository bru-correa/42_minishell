/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:29:56 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/29 16:35:35 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_list(t_slist **list)
{
	t_slist	*current_data;
	char	*joined_data;
	char	*temp;

	current_data = *list;
	joined_data = ft_strdup("");
	while (current_data != NULL)
	{
		temp = joined_data;
		joined_data = ft_strjoin(temp, current_data->data);
		free(temp);
		current_data = current_data->next;
	}
	clear_slist(list);
	return (joined_data);
}
