/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:52:15 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/16 23:41:40 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_cmd_count(t_slist **tokens);
static int	*init_children_pids(int cmd_count);

t_pipeline	*create_pipeline(t_slist **tokens)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (pipeline == NULL)
		return (NULL);
	pipeline->cmd_count = get_cmd_count(tokens);
	pipeline->cmds = create_cmds(tokens, pipeline->cmd_count);
	pipeline->children_pids = init_children_pids(pipeline->cmd_count);
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

static int	*init_children_pids(int cmd_count)
{
	int	*children_pid;
	int	length;

	if (cmd_count <= 1)
		return (NULL);
	length = sizeof(int) * (cmd_count + 1);
	children_pid = malloc(length);
	if (children_pid == NULL)
		return (NULL);
	ft_bzero(children_pid, length);
	return (children_pid);
}
