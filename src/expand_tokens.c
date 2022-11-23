/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:51:56 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/23 17:24:14 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* NOTE:
 * Get each individual token
 * Create a sublist with that token, with the string and the expanded vars
 * Join the whole list to a single str and assign it to that token
*/

// TODO: Change t_token to a generic str_list

static int	check_single_quote(char c, int squote);
static int	get_var_end_index(char *str, int start);
static char	*get_expanded_value(t_token *token, t_env_var **envl);
static char	*get_var_value(char *str, int start, int end, t_env_var **envl);
static t_token	*add_sub_token(char *str, int start, int end,
		t_token *sub_token);
static char	*join_sub_tokens(t_token *sub_tokens);

void	expand_tokens(t_token *token_head, t_env_var **envl)
{
	t_token	*current_token;
	char	*expanded_value;

	current_token = token_head;
	while (current_token != NULL)
	{
		expanded_value = get_expanded_value(current_token, envl);
		free(current_token->value);
		current_token->value = expanded_value;
		current_token = current_token->next;
	}
}

static char	*get_expanded_value(t_token *token, t_env_var **envl)
{
	int		start;
	int		current;
	t_token	*sub_tokens;
	char	*var_value;
	int		squote;
	char	*expanded_value;

	sub_tokens = NULL;
	start = 0;
	current = start;
	squote = FALSE;
	while (token->value[start] != '\0')
	{
		squote = check_single_quote(token->value[current], squote);
		if (token->value[current] == '\0')
		{
			sub_tokens = add_sub_token(token->value, start, current - 1, sub_tokens);
			start = current;
		}
		else if (token->value[current] == '$' && squote == FALSE)
		{
			if (current == start)
			{
				// Expand $
				current = get_var_end_index(token->value, start);
				var_value = get_var_value(token->value, start, current, envl);
				sub_tokens = append_token(sub_tokens, var_value);
				current++;
			}
			else
			{
				// Get str until $
				sub_tokens = add_sub_token(token->value, start, current - 1, sub_tokens);
			}
			start = current;
		}
		else
			current++;
	}
	expanded_value = join_sub_tokens(sub_tokens);
	return (expanded_value);
}

static t_token	*add_sub_token(char *str, int start, int end,
					t_token *sub_token)
{
	char	*value;

	value = ft_substr(str, start, end - start + 1);
	sub_token = append_token(sub_token, value);
	return (sub_token);
}

// When the token is just '$', dont expand and return '$'
static char	*get_var_value(char *str, int start, int end, t_env_var **envl)
{
	char	*var_name;
	char	*var_value;

	if (start == end)
		return (ft_strdup("$"));
	var_name = ft_substr(str, start + 1, end - start);
	var_value = search_env_var(envl, var_name);
	free(var_name);
	return (var_value);
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

static char	*join_sub_tokens(t_token *sub_tokens)
{
	t_token	*current_token;
	char	*joined_str;
	char	*temp;

	current_token = sub_tokens;
	joined_str = ft_strdup("");
	while (current_token != NULL)
	{
		temp = joined_str;
		joined_str = ft_strjoin(temp, current_token->value);
		free(temp);
		current_token = current_token->next;
	}
	sub_tokens = free_tokens(sub_tokens);
	return (joined_str);
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
