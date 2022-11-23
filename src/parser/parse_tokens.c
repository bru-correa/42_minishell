/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:58:26 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/04 14:34:22 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	get_cmds_count(t_token *token_head);

// t_cmd	*get_cmds(t_token *token_head)
// {
// 	int	cmds_count;

// 	cmds_count = get_cmds_count(token_head);
// }

// static int	get_cmds_count(t_token *token_head)
// {
// 	int		count;
// 	t_token	*current_token;

// 	count = 1;
// 	current_token = token_head;
// 	while (current_token != NULL)
// 	{
// 		if (ft_strncmp(current_token->value, "|", 2) == 0)
// 			count++;
// 		current_token = current_token->next;
// 	}
// 	return (count);
// }
