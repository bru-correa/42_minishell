/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:04:24 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/01/05 21:17:19 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>

// TODO: Refactor all functions that use env_list to use the global `g_minish`
void	repl(void)
{
	char		*input;
	t_pipeline	*pipeline;

	while (1)
	{
		input = readline(">$ ");
		if (input == NULL)
		{
			clear_env_list(g_minish.env_list);
			break ;
		}
		add_history(input);
		pipeline = parse_input(input, g_minish.env_list);
		free(input);
		if (pipeline == NULL)
			continue ;
		exec_pipeline(pipeline, g_minish.env_list);
		clear_pipeline(pipeline);
	}
}
