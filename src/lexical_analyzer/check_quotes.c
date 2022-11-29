/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:34:42 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/29 13:48:09 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_quote_end(char *data, int start, char quote);
static int	check_quote(char *data, int index);

int	check_unclosed_quotes(char *data)
{
	int	i;

	i = 0;
	while (data[i] != '\0')
	{
		if (data[i] == '\'')
		{
			i = get_quote_end(data, i, '\'');
			if (check_quote(data, i) == FAILURE)
				return (FAILURE);
		}
		else if (data[i] == '"')
		{
			i = get_quote_end(data, i, '"');
			if (check_quote(data, i) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

// Check if the `index` is not valid
static int	check_quote(char *data, int index)
{
	if (data[index] == '\0')
	{
		print_quote_error();
		return (FAILURE);
	}
	return (SUCCESS);
}

// Return the '\0' index if not found
static int	get_quote_end(char *data, int start, char quote)
{
	int	i;

	i = start + 1;
	while (data[i] != '\0')
	{
		if (data[i] == quote)
			return (i);
		i++;
	}
	return (i);
}
