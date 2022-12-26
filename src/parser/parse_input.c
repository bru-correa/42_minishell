/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:58:26 by bcorrea-          #+#    #+#             */
/*   Updated: 2022/12/21 11:56:40 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipeline	*parse_input(char *input, t_env_var **env_list)
{
	t_slist		**tokens;
	t_pipeline	*pipeline;

	tokens = create_token_list(input, env_list);
	if (tokens == NULL)
		return (NULL);
	pipeline = create_pipeline(tokens);
	clear_slist(tokens);
	return (pipeline);
}
