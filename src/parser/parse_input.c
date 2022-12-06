/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:58:26 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/06 18:21:28 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Create the command list
t_cmd	**parse_input(char *input, t_env_var **env_list)
{
	t_slist	**tokens;
	t_cmd	**cmds;

	cmds = NULL;
	tokens = get_tokens(input);
	if (tokens == NULL)
		return (NULL);
	tokens = expand_tokens(tokens, env_list);
	if (tokens == NULL)
		return (NULL);
	// Create the command list
	clear_slist(tokens);
	return (cmds);
}

// WARNING: OLD CODE!!!

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
