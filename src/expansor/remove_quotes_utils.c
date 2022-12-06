/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:22:09 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/06 17:31:49 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_next_quote(char *data)
{
	int	i;

	i = 0;
	while (data[i] != '\0')
	{
		if (data[i] == '\'' || data[i] == '"')
			return (i);
		i++;
	}
	return (i);
}

int	get_quote_length(char *data)
{
	int		i;
	char	quote;

	quote = *data;
	i = 0;
	while (data[i + 1] != quote)
		i++;
	return (i);
}
