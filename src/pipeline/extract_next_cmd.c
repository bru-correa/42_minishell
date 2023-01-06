/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_next_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:48:09 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/05 10:23:48 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		split_arg(t_slist **tokens, t_slist *token, t_slist **arg_list);
static void		split_rdir(t_slist **tokens, t_slist *token,
					t_slist **rdir_list);
static int		check_rdir(int type);
static t_cmd	*create_cmd(t_slist **arg_list, t_slist **rdir_list);

t_cmd	*extract_next_cmd(t_slist **tokens)
{
	t_slist	**arg_list;
	t_slist	**rdir_list;
	t_cmd	*cmd;

	if (*tokens == NULL)
		return (NULL);
	arg_list = create_slist();
	rdir_list = create_slist();
	while (*tokens != NULL)
	{
		if ((*tokens)->type == T_ARG)
			split_arg(tokens, *tokens, arg_list);
		else if (check_rdir((*tokens)->type) == TRUE)
			split_rdir(tokens, *tokens, rdir_list);
		else if ((*tokens)->type == T_PIPE)
		{
			split_rdir(tokens, *tokens, rdir_list);
			break ;
		}
	}
	cmd = create_cmd(arg_list, rdir_list);
	return (cmd);
}

static void	split_arg(t_slist **tokens, t_slist *token, t_slist **arg_list)
{
	t_slist	*arg_token;

	arg_token = token;
	token = token->next;
	pop_slist_node(tokens, arg_token);
	append_node_to_slist(arg_list, arg_token);
}

static void	split_rdir(t_slist **tokens, t_slist *token, t_slist **rdir_list)
{
	t_slist	*rdir_token;

	rdir_token = token;
	token = token->next;
	pop_slist_node(tokens, rdir_token);
	append_node_to_slist(rdir_list, rdir_token);
}

static int	check_rdir(int type)
{
	if (type == T_RDIR_IN || type == T_RDIR_OUT)
		return (TRUE);
	else if (type == T_RDIR_APPEND || type == T_RDIR_HERE)
		return (TRUE);
	return (FALSE);
}

static t_cmd	*create_cmd(t_slist **arg_list, t_slist **rdir_list)
{
	char	**args;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	args = slist_to_str_array(arg_list);
	cmd->args = args;
	if (*rdir_list == NULL)
	{
		free(rdir_list);
		cmd->rdir_list = NULL;
	}
	else
		cmd->rdir_list = rdir_list;
	return (cmd);
}
