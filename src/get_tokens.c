/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:27:45 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/10/31 14:51:58 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static t_token	*add_new_token(const char *cmdline, size_t length,
					t_token *token_head);
static int		get_next_split(char *cmdline, int start);
static int		skip_spaces(char *cmdline, int start);
static void		check_quotes(char c, int *single_quote, int *double_quote);

t_token	*get_tokens(char *cmdline)
{
	int		start;
	int		i;
	t_token	*token_head;

	start = skip_spaces(cmdline, 0);
	i = start;
	token_head = NULL;
	while (cmdline[i] != '\0')
	{
		i = get_next_split(cmdline, start);
		token_head = add_new_token(&cmdline[start], i - start, token_head);
		if (token_head == NULL)
			return (NULL);
		if (cmdline[i] != '\0')
			start = skip_spaces(cmdline, i);
	}
	return (token_head);
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

static t_token	*add_new_token(const char *cmdline, size_t length,
		t_token *token_head)
{
	char	*value;

	value = ft_substr(cmdline, 0, length);
	token_head = append_token(token_head, value);
	return (token_head);
}

static int	skip_spaces(char *cmdline, int start)
{
	int	i;

	i = start;
	while (cmdline[i] != '\0' && cmdline[i] == ' ')
		i++;
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
