/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens_types.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:38:12 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/26 12:14:42 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_token_type(t_slist *token);
static int	is_redir_type(int type);

t_slist	**set_tokens_types(t_slist **tokens)
{
	t_slist	*current;
	t_slist	*temp;

	if (*tokens == NULL)
		return (tokens);
	current = *tokens;
	while (current != NULL)
	{
		set_token_type(current);
		if (is_redir_type(current->type) == TRUE)
		{
			temp = current;
			current = current->next;
			current->type = temp->type;
			tokens = delete_from_slist(tokens, temp);
		}
		current = current->next;
	}
	return (tokens);
}

static void	set_token_type(t_slist *token)
{
	if (ft_strncmp(token->data, ">", 2) == 0)
		token->type = T_RDIR_OUT;
	else if (ft_strncmp(token->data, "<", 2) == 0)
		token->type = T_RDIR_IN;
	else if (ft_strncmp(token->data, ">>", 3) == 0)
		token->type = T_RDIR_APPEND;
	else if (ft_strncmp(token->data, "<<", 3) == 0)
		token->type = T_RDIR_HERE;
	else if (ft_strncmp(token->data, "|", 2) == 0)
		token->type = T_PIPE;
	else
		token->type = T_ARG;
}

static int	is_redir_type(int type)
{
	if (type == T_RDIR_IN || type == T_RDIR_OUT
		|| type == T_RDIR_APPEND || type == T_RDIR_HERE)
	{
		return (TRUE);
	}
	return (FALSE);
}
