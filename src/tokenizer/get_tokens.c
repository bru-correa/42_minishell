/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:27:45 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/02/18 09:33:31 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_slist	**add_new_token(const char *cmdline, size_t length,
					t_slist **tokens);
static int		get_next_split(char *cmdline, int start);
static int		skip_spaces(char *cmdline, int start);
static void		check_quotes(char c, int *single_quote, int *double_quote);

t_slist	**get_tokens(char *cmdline)
{
	int		start;
	int		i;
	t_slist	**tokens;

	start = skip_spaces(cmdline, 0);
	i = start;
	tokens = create_slist();
	if (tokens == NULL)
		return (NULL);
	while (cmdline[i] != '\0')
	{
		i = get_next_split(cmdline, start);
		tokens = add_new_token(&cmdline[start], i - start, tokens);
		if (tokens == NULL)
			return (NULL);
		if (cmdline[i] != '\0')
			start = skip_spaces(cmdline, i);
	}
	return (tokens);
}

// Return the index of the next delimiter
static int	get_next_split(char *cmdline, int start)
{
	int	single_quote;
	int	double_quote;
	int	i;
	int	delimiter;

	single_quote = FALSE;
	double_quote = FALSE;
	i = start;
	while (cmdline[i] != '\0')
	{
		check_quotes(cmdline[i], &single_quote, &double_quote);
		if (single_quote == FALSE && double_quote == FALSE)
		{
			delimiter = get_delimiter_index(cmdline, i, start);
			if (delimiter != -1)
				return (delimiter);
		}
		i++;
	}
	return (i);
}

t_slist	**add_new_token(const char *cmdline, size_t length,
		t_slist **tokens)
{
	char	*data;

	data = ft_substr(cmdline, 0, length);
	tokens = append_to_slist(tokens, data);
	return (tokens);
}

static int	skip_spaces(char *cmdline, int start)
{
	int	i;

	i = start;
	while (cmdline[i] != '\0')
	{
		if (cmdline[i] != ' ' && cmdline[i] != '\t'
			&& cmdline[i] != '\r' && cmdline[i] != '\n'
			&& cmdline[i] != '\v')
			break ;
		i++;
	}
	return (i);
}

static void	check_quotes(char c, int *single_quote, int *double_quote)
{
	if (c == '\'')
	{
		if (*single_quote == FALSE)
			*single_quote = TRUE;
		else
			*single_quote = FALSE;
	}
	else if (c == '"')
	{
		if (*double_quote == FALSE)
			*double_quote = TRUE;
		else
			*double_quote = FALSE;
	}
}
