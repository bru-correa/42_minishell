/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:52:15 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/13 04:04:10 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_cmd_count(t_slist **tokens);

t_pipeline	*create_pipeline(t_slist **tokens)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (pipeline == NULL)
		return (NULL);
	pipeline->cmd_count = get_cmd_count(tokens);
	pipeline->cmds = create_cmds(tokens, pipeline->cmd_count);
	return (pipeline);
}

static int	get_cmd_count(t_slist **tokens)
{
	int		count;
	t_slist	*current;

	if (*tokens == NULL)
		return (0);
	count = 1;
	current = *tokens;
	while (current != NULL)
	{
		if (current->type == T_PIPE)
			count++;
		current = current->next;
	}
	return (count);
}
