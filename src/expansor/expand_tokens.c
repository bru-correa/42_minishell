/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:52:19 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/24 19:01:59 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_expanded_data(char *data, t_env_var **envl);
static t_slist	**get_split_data(char *data, t_slist **data_list,
					t_env_var **envl);
static char		*join_data_list(t_slist **data_list);

t_slist	**expand_tokens(t_slist **tokens, t_env_var **envl)
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
	tokens = clear_empty_tokens(tokens);
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
	expanded_data = join_data_list(data_list);
	return (expanded_data);
}

static t_slist	**get_split_data(char *data, t_slist **data_list,
		t_env_var **envl)
{
	int		start;
	int		i;
	int		squote;

	start = 0;
	i = start;
	squote = FALSE;
	while (data[start] != '\0')
	{
		squote = toggle_quote_state(squote, data[i], '\'');
		if (data[i] == '\0')
		{
			data_list = split_token_data(&data[start], i - start, data_list);
			start = i;
		}
		else if (data[i] == '$' && squote == FALSE)
		{
			i += expand_var_data(&data[start], i - start, data_list, envl);
			start = i;
		}
		else
			i++;
	}
	return (data_list);
}

// Return "" if data_list is empty
static char	*join_data_list(t_slist **data_list)
{
	t_slist	*current_data;
	char	*joined_data;
	char	*temp;

	current_data = *data_list;
	joined_data = ft_strdup("");
	while (current_data != NULL)
	{
		temp = joined_data;
		joined_data = ft_strjoin(temp, current_data->data);
		free(temp);
		current_data = current_data->next;
	}
	clear_slist(data_list);
	return (joined_data);
}
