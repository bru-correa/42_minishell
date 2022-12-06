/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:02:01 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/06 17:40:38 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_unquoted_data(char *data);
static t_slist	**get_split_data(char *data);
static int		split_prev_data(char *data, int length, t_slist **data_list);
static int		split_quoted(char *data, int length, t_slist **data_list);

t_slist	**remove_quotes(t_slist **tokens)
{
	t_slist	*current_token;
	char	*unquoted_data;

	current_token = *tokens;
	while (current_token != NULL)
	{
		if (ft_strchr(current_token->data, '\'') != NULL
			|| ft_strchr(current_token->data, '"') != NULL)
		{
			unquoted_data = get_unquoted_data(current_token->data);
			free(current_token->data);
			current_token->data = unquoted_data;
		}
		current_token = current_token->next;
	}
	return (tokens);
}

static char	*get_unquoted_data(char *data)
{
	t_slist	**data_list;
	char	*unquoted_data;

	data_list = get_split_data(data);
	unquoted_data = join_list(data_list);
	return (unquoted_data);
}

static t_slist	**get_split_data(char *data)
{
	int		i;
	int		length;
	t_slist	**data_list;

	data_list = create_slist();
	i = 0;
	while (data[i] != '\0')
	{
		length = get_next_quote(&data[i]);
		if (length > 0)
			i += split_prev_data(&data[i], length, data_list);
		if (data[i] == '\'' || data[i] == '"')
		{
			length = get_quote_length(&data[i]);
			i += split_quoted(&data[i], length, data_list);
		}
	}
	return (data_list);
}

static int	split_prev_data(char *data, int length, t_slist **data_list)
{
	char	*prev_data;

	prev_data = ft_substr(data, 0, length);
	append_to_slist(data_list, prev_data);
	return (length);
}

// Add 2 to length because of the quotes offset
static int	split_quoted(char *data, int length, t_slist **data_list)
{
	char	*quoted_data;

	if (length == 0)
	{
		quoted_data = ft_strdup("");
		append_to_slist(data_list, quoted_data);
		return (length + 2);
	}
	quoted_data = ft_substr(data, 1, length);
	append_to_slist(data_list, quoted_data);
	return (length + 2);
}
