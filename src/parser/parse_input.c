/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:58:26 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/02 11:15:04 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipeline	*parse_input(char *input, t_env_var **env_list)
{
	t_slist		**tokens;
	t_pipeline	*pipeline;

	if (input == NULL)
		return (NULL);
	tokens = create_token_list(input, env_list);
	if (tokens == NULL)
		return (NULL);
	pipeline = create_pipeline(tokens);
	clear_slist(tokens);
	return (pipeline);
}
