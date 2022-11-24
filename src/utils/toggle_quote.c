/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:08:32 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/11/24 12:19:07 by bcorrea-         ###   ########.fr       */
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
