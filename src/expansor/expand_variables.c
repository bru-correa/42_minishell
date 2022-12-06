/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:52:19 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/06 17:51:35 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_expanded_data(char *data, t_env_var **envl);
static t_slist	**get_split_data(char *data, t_slist **data_list,
					t_env_var **envl);

t_slist	**expand_variables(t_slist **tokens, t_env_var **envl)
{
	t_slist	*current_token;
	char	*expanded_data;

	current_token = *tokens;
	while (current_token != NULL)
	{
		expanded_data = get_expanded_data(current_token->data, envl);
		free(current_token->data);
		current_token->data = expanded_data;
		current_token = current_token->next;
	}
	return (tokens);
}

static char	*get_expanded_data(char *data, t_env_var **envl)
{
	t_slist	**data_list;
	char	*expanded_data;

	data_list = create_slist();
	if (data_list == NULL)
		return (NULL);
	data_list = get_split_data(data, data_list, envl);
	expanded_data = join_list(data_list);
	return (expanded_data);
}

static t_slist	**get_split_data(char *data, t_slist **data_list,
		t_env_var **envl)
{
	int		start;
	int		i;
	int		squote;
	int		dquote;

	start = 0;
	i = start;
	squote = FALSE;
	dquote = FALSE;
	while (data[i] != '\0')
	{
		update_quote_state(data[i], &squote, &dquote);
		if (data[i] == '$' && squote == FALSE)
		{
			i += expand_var_data(&data[start], i - start, data_list, envl);
			start = i;
		}
		else
			i++;
	}
	data_list = split_token_data(&data[start], i - start, data_list);
	return (data_list);
}
