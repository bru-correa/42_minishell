/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:45:46 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/08 14:28:29 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_invalid_chars(char c);

int	check_special_chars(char *data)
{
	int	i;
	int	squote;
	int	dquote;

	i = 0;
	squote = FALSE;
	dquote = FALSE;
	while (data[i] != '\0')
	{
		update_quote_state(data[i], &squote, &dquote);
		if (squote == FALSE && dquote == FALSE)
		{
			if (check_invalid_chars(data[i]) == FAILURE)
			{
				print_special_char_error(data[i]);
				return (FAILURE);
			}
		}
		i++;
	}
	return (SUCCESS);
}

static int	check_invalid_chars(char c)
{
	if (c == '\\' || c == '#')
		return (FAILURE);
	else if (c == '[' || c == ']')
		return (FAILURE);
	else if (c == '!' || c == '*')
		return (FAILURE);
	else if (c == '{' || c == '}')
		return (FAILURE);
	else if (c == '(' || c == ')')
		return (FAILURE);
	else if (c == ';' || c == '~')
		return (FAILURE);
	else if (c == '~' || c == '&')
		return (FAILURE);
	else if (c == '`')
		return (FAILURE);
	return (SUCCESS);
}
