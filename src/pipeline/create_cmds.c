/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:22:03 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/23 11:50:45 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	**init_cmds(t_slist **tokens, int cmd_count);

t_cmd	**create_cmds(t_slist **tokens, int cmd_count)
{
	t_cmd	**cmds;
	int		i;

	cmds = init_cmds(tokens, cmd_count);
	i = 0;
	while (i < cmd_count)
	{
		cmds[i] = extract_next_cmd(tokens);
		i++;
	}
	cmds[cmd_count] = NULL;
	return (cmds);
}

static t_cmd	**init_cmds(t_slist **tokens, int cmd_count)
{
	t_cmd	**cmds;

	if (*tokens == NULL)
		return (NULL);
	cmds = malloc(sizeof(t_cmd *) * (cmd_count + 1));
	if (cmds == NULL)
		return (NULL);
	return (cmds);
}
