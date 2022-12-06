/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:08:32 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/05 20:53:21 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	toggle_quote_state(int quote_state, char c, char quote_char)
{
	if (c == quote_char)
	{
		if (quote_state == TRUE)
			return (FALSE);
		return (TRUE);
	}
	return (quote_state);
}

void	update_quote_state(char c, int *squote, int *dquote)
{
	if (c == '\'')
	{
		if (*dquote == FALSE)
			*squote = toggle_quote_state(*squote, c, '\'');
	}
	else if (c == '"')
	{
		if (*squote == FALSE)
			*dquote = toggle_quote_state(*dquote, c, '"');
	}
}

t_quotes	*create_quotes(void)
{
	t_quotes	*quotes;

	quotes = malloc(sizeof(t_quotes));
	if (quotes == NULL)
		return (NULL);
	quotes->s = FALSE;
	quotes->d = FALSE;
	return (quotes);
}
