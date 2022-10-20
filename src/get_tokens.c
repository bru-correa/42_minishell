/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bcorrea->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:32:24 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/10/19 22:02:50 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	skip_spaces(char *cmdline, int start);
static void	check_quotes(char c, int *single_quote, int *double_quote);
static int	get_token_type(char *value);
static int	check_alloc_errors(t_token *token, char *value);

t_token	*get_tokens(char *cmdline)
{
	int		start;
	int		i;
	t_token	*token;
	int		single_quote;
	int		double_quote;
	char	*value;
	int		type;

	start = skip_spaces(cmdline, 0);
	i = start;
	token = NULL;
	single_quote = FALSE;
	double_quote = FALSE;
	while (cmdline[start] != '\0')
	{
		if (cmdline[i] == '\0')
		{
			value = ft_substr(cmdline, start, i - start);
			type = get_token_type(value);
			token = add_token(token, type, value);
			if (check_alloc_errors(token, value) == TRUE)
				return (NULL);
			start = skip_spaces(cmdline, i);
			i = start;
		}
		check_quotes(cmdline[i], &single_quote, &double_quote);
		if (cmdline[i] == ' ' && single_quote == FALSE && double_quote == FALSE)
		{
			value = ft_substr(cmdline, start, i - start);
			type = get_token_type(value);
			token = add_token(token, type, value);
			if (check_alloc_errors(token, value) == TRUE)
				return (NULL);
			start = skip_spaces(cmdline, i);
			i = start;
		}
		else
			i++;
	}
	return (token);
}

// Return the first non space char or the end of the string
static int	skip_spaces(char *cmdline, int start)
{
	int	i;

	i = start;
	while (cmdline[i] != '\0' && cmdline[i] == ' ')
		i++;
	return (i);
}

// Toggle single and double quote mode if it finds '\'' or '"' respectively
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

static int	get_token_type(char *value)
{
	if (ft_strncmp(value, "|", 2) == 0)
		return (TK_PIPE);
	else if (ft_strncmp(value, "<", 2))
		return (TK_INPUT);
	else if (ft_strncmp(value, ">", 2))
		return (TK_OUTPUT);
	else if (ft_strncmp(value, "<<", 3))
		return (TK_HEREDOC);
	else if (ft_strncmp(value, ">>", 3))
		return (TK_APPEND);
	else
		return (TK_WORD);
}

static int	check_alloc_errors(t_token *token, char *value)
{
	if (token == NULL)
	{
		free(value);
		return (TRUE);
	}
	else if (value == NULL)
	{
		free_tokens(token);
		return (TRUE);
	}
	else
		return (FALSE);
}
