/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:51:56 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/23 20:17:53 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* NOTE:
 * Get each individual token
 * Create a sublist with that token, with the string and the expanded vars
 * Join the whole list to a single str and assign it to that token
*/

static char		*get_expanded_data(t_slist *token, t_env_var **envl);
static t_slist	**add_to_data_list(char *str, int start, int end,
					t_slist **data_list);
static char		*get_var_data(char *str, int start, int end, t_env_var **envl);
static int		get_var_end_index(char *str, int start);
static char		*join_data_list(t_slist **data_list);
static int		check_single_quote(char c, int squote);

// TODO: Expand tokens return **tokens and expand tokens also clear empty
t_slist	**expand_tokens(t_slist **tokens, t_env_var **envl)
{
	t_slist	*current_token;
	char	*expanded_data;

	current_token = *tokens;
	while (current_token != NULL)
	{
		expanded_data = get_expanded_data(current_token, envl);
		free(current_token->data);
		current_token->data = expanded_data;
		current_token = current_token->next;
	}
	tokens = clear_empty_tokens(tokens);
	return (tokens);
}

static char	*get_expanded_data(t_slist *token, t_env_var **envl)
{
	int		start;
	int		current;
	t_slist	**data_list;
	char	*var_data;
	int		squote;
	char	*expanded_data;

	data_list = create_slist();
	if (data_list == NULL)
		return (NULL);
	start = 0;
	current = start;
	squote = FALSE;
	while (token->data[start] != '\0')
	{
		squote = check_single_quote(token->data[current], squote);
		if (token->data[current] == '\0')
		{
			data_list = add_to_data_list(token->data, start, current - 1, data_list);
			start = current;
		}
		else if (token->data[current] == '$' && squote == FALSE)
		{
			if (current == start)
			{
				// Expand $
				current = get_var_end_index(token->data, start);
				var_data = get_var_data(token->data, start, current, envl);
				data_list = append_to_slist(data_list, var_data);
				current++;
			}
			else
			{
				// Get str until $
				data_list = add_to_data_list(token->data, start, current - 1, data_list);
			}
			start = current;
		}
		else
			current++;
	}
	expanded_data = join_data_list(data_list);
	return (expanded_data);
}

static t_slist	**add_to_data_list(char *str, int start, int end,
					t_slist **data_list)
{
	char	*data;

	data = ft_substr(str, start, end - start + 1);
	data_list = append_to_slist(data_list, data);
	return (data_list);
}

// When the token is just '$', dont expand and return '$'
static char	*get_var_data(char *str, int start, int end, t_env_var **envl)
{
	char	*var_name;
	char	*var_data;

	if (start == end)
		return (ft_strdup("$"));
	var_name = ft_substr(str, start + 1, end - start);
	var_data = search_env_var(envl, var_name);
	free(var_name);
	return (var_data);
}

static int	get_var_end_index(char *str, int start)
{
	int	end;

	end = start + 1;
	while (str[end] != '\0')
	{
		if (ft_isalnum(str[end]) == 0 && str[end] != '_')
			return (end - 1);
		end++;
	}
	return (end - 1);
}

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

static int	check_single_quote(char c, int squote)
{
	if (c == '\'')
	{
		if (squote == TRUE)
			return (FALSE);
		else
			return (TRUE);
	}
	return (squote);
}
